#include "SDLAudioService.h"
#include <unordered_map>
#include <SDL_mixer.h>
#include <iostream>

#include "ResourceManager.h"

struct SoundAndChannel
{
    Mix_Chunk* Sound;
    int SoundChannel;
};

class SDLAudioImpl
{
public:
    SDLAudioImpl()
	{
        const int maxChannels = 8;
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, maxChannels, 2048);
    }

    ~SDLAudioImpl()
    {
        for (auto& [_, chunk] : m_LoadedChunks)
        {
            Mix_FreeChunk(chunk);
        }
        for (auto& [_, music] : m_LoadedMusic)
        {
            Mix_FreeMusic(music);
        }

        Mix_CloseAudio();
    }

    void AddSound(const std::string& soundName, int soundChannel, const char* filePathForSound)
    {
        const auto fullPath = m_dataPath / filePathForSound;
        const auto filename = std::filesystem::path(fullPath).filename().string();

        Mix_Chunk* chunk = nullptr;

        // Check if this file has already been loaded
        auto it = m_LoadedChunks.find(filename);
        if (it != m_LoadedChunks.end())
        {
            chunk = it->second;
        }
        else
        {
            chunk = Mix_LoadWAV(fullPath.string().c_str());
            if (!chunk)
            {
                throw std::runtime_error(std::string("Failed to load sound: ") + Mix_GetError());
            }
            m_LoadedChunks[filename] = chunk;
        }

        m_Sounds.emplace(soundName, SoundAndChannel{ chunk, soundChannel });
    }

    void AddMusic(const std::string& musicName, const char* filePathForMusic)
    {
        const auto fullPath = m_dataPath / filePathForMusic;
        const auto filename = std::filesystem::path(fullPath).filename().string();

        // Check if this music file has already been loaded
        auto it = m_LoadedMusic.find(filename);
        if (it != m_LoadedMusic.end())
        {
            return;
        }

        Mix_Music* music = Mix_LoadMUS(fullPath.string().c_str());
        if (!music)
        {
            throw std::runtime_error(std::string("Failed to load music: ") + Mix_GetError());
        }
        m_LoadedMusic[filename] = music;
			
        m_Musics.emplace(musicName, music);
    }

    void PlaySound(const std::string& soundName, int volume, int loops) const
    {
        auto soundAndChannel = m_Sounds.find(soundName)->second;
    	soundAndChannel.SoundChannel = Mix_PlayChannel(soundAndChannel.SoundChannel, soundAndChannel.Sound, loops);
        Mix_VolumeChunk(soundAndChannel.Sound, volume);
    }

    void PlayMusic(const std::string& musicName, int volume, int loops) const
    {
        auto it = m_Musics.find(musicName);
        if (it != m_Musics.end())
        {
            Mix_PlayMusic(it->second, loops);
            Mix_VolumeMusic(volume);
        }
        else
        {
            throw std::runtime_error("Music not found: " + musicName);
        }
    }

    void PauseSound(const std::string& soundName) const
    {
        const auto soundAndChannel = m_Sounds.find(soundName);
    	Mix_Pause(soundAndChannel->second.SoundChannel);
    }

    static void PauseMusic()
    {
        Mix_PauseMusic();
    }

    static void PauseAllSounds()
	{
        Mix_Pause(-1);
    }

    void StopSound(const std::string& soundName) const
    {
        const auto soundAndChannel = m_Sounds.find(soundName);
    	Mix_HaltChannel(soundAndChannel->second.SoundChannel);
    }

    static void StopAllSounds()
	{
        Mix_HaltChannel(-1);
    }

    static void SetAllAudioVolume(const int volume)
    {
        Mix_Volume(-1, volume);
    }

    static void SetChannelVolume(int channel, int volume)
    {
        Mix_Volume(channel, volume);
    }

    void SetSoundVolume(const std::string& soundName, const int volume) const
    {
        const auto soundAndChannel = m_Sounds.find(soundName)->second;
        Mix_VolumeChunk(soundAndChannel.Sound, volume);
    }

    static void SetMusicVolume(const int volume)
    {
        Mix_VolumeMusic(volume);
    }

    void SetDataPath(const std::filesystem::path& data)
    {
        m_dataPath = data;
    }

private:
    std::unordered_map<std::string, SoundAndChannel> m_Sounds;
    std::unordered_map<std::string, Mix_Chunk*> m_LoadedChunks;
    std::unordered_map<std::string, Mix_Music*> m_LoadedMusic;
    std::unordered_map<std::string, Mix_Music*> m_Musics;
    std::filesystem::path m_dataPath;
};

SDLAudio::SDLAudio(const std::filesystem::path& data)
{
    m_pImpl = std::make_unique<SDLAudioImpl>();
    m_pImpl->SetDataPath(data);

    m_WorkerThread = std::thread([this]() { this->Run(); });
}

SDLAudio::~SDLAudio()
{
    {
        std::lock_guard<std::mutex> lock(m_QueueMutex);
        m_Running = false;
    }
    m_Condition.notify_one(); // wake the thread if it's sleeping

    if (m_WorkerThread.joinable())
        m_WorkerThread.join();
}

void SDLAudio::AddSound(std::string soundName, int soundChannel, const char* filePathForSound)
{
    {
        std::lock_guard<std::mutex> lock(m_QueueMutex);
		m_EventQueue.emplace([this, soundName, soundChannel, filePathForSound]() {m_pImpl->AddSound(soundName, soundChannel, filePathForSound);});
	}
	m_Condition.notify_one();
}

void SDLAudio::AddMusic(const std::string& musicName, const char* filePathForMusic)
{
    {
        std::lock_guard<std::mutex> lock(m_QueueMutex);
        m_EventQueue.emplace([this, musicName, filePathForMusic]() { m_pImpl->AddMusic(musicName, filePathForMusic); });
    }
    m_Condition.notify_one();
}

void SDLAudio::PlaySound(std::string soundName, int volume, int loops)
{
    {
        std::lock_guard<std::mutex> lock(m_QueueMutex);
        m_EventQueue.emplace([this, loops, soundName, volume]() { m_pImpl->PlaySound(soundName, volume ,loops);});
    }
    m_Condition.notify_one();
}

void SDLAudio::PlayMusic(const std::string& musicName, int volume, int loops)
{
    {
        std::lock_guard<std::mutex> lock(m_QueueMutex);
        m_EventQueue.emplace([this, loops, musicName, volume]() { m_pImpl->PlayMusic(musicName, volume, loops); });
    }
    m_Condition.notify_one();
}


void SDLAudio::PauseSound(std::string soundName)
{
    {
        std::lock_guard<std::mutex> lock(m_QueueMutex);
        m_EventQueue.emplace([this, soundName]() { m_pImpl->PauseSound(soundName); });
    }
    m_Condition.notify_one();
}

void SDLAudio::PauseMusic()
{
    {
        std::lock_guard<std::mutex> lock(m_QueueMutex);
        m_EventQueue.emplace([this]() {m_pImpl->PauseMusic();});
    }
    m_Condition.notify_one();
}

void SDLAudio::PauseAllSounds()
{
    {
        std::lock_guard<std::mutex> lock(m_QueueMutex);
        m_EventQueue.emplace([this]() { m_pImpl->PauseAllSounds(); });
    }
    m_Condition.notify_one();
}

void SDLAudio::StopSound(std::string soundName)
{
    {
        std::lock_guard<std::mutex> lock(m_QueueMutex);
        m_EventQueue.emplace([this, soundName]() {m_pImpl->StopSound(soundName);});
    }
    m_Condition.notify_one();
}

void SDLAudio::StopAllSounds()
{
    {
        std::lock_guard<std::mutex> lock(m_QueueMutex);
        m_EventQueue.emplace([this]() {  m_pImpl->StopAllSounds(); });
    }
    m_Condition.notify_one();
}

void SDLAudio::SetAllAudioVolume(int volume)
{
    {
        std::lock_guard<std::mutex> lock(m_QueueMutex);
        m_EventQueue.emplace([this, volume]() {  m_pImpl->SetAllAudioVolume(volume); });
    }
    m_Condition.notify_one();
}

void SDLAudio::SetChannelVolume(int channel, int volume)
{
    {
        std::lock_guard<std::mutex> lock(m_QueueMutex);
        m_EventQueue.emplace([this, volume, channel]() {  m_pImpl->SetChannelVolume(channel ,volume); });
    }
    m_Condition.notify_one();
}

void SDLAudio::SetSoundVolume(std::string soundName, int volume)
{
    {
        std::lock_guard<std::mutex> lock(m_QueueMutex);
        m_EventQueue.emplace([this, volume, soundName]() {  m_pImpl->SetSoundVolume(soundName ,volume); });
    }
    m_Condition.notify_one();
}

void SDLAudio::SetMusicVolume(int volume)
{
    {
        std::lock_guard<std::mutex> lock(m_QueueMutex);
        m_EventQueue.emplace([this, volume]() {  m_pImpl->SetMusicVolume(volume); });
    }
    m_Condition.notify_one();
}

void SDLAudio::Run()
{
    while (m_Running)
    {
        std::function<void()> task;

        {
            std::unique_lock<std::mutex> lock(m_QueueMutex);
            m_Condition.wait(lock, [this]() {
                return !m_EventQueue.empty() || !m_Running;
                });

            if (!m_Running && m_EventQueue.empty())
                return;

            task = std::move(m_EventQueue.front());
            m_EventQueue.pop();
        }

        task();
    }
}

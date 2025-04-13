#include "SDLAudio.h"
#include <unordered_map>
#include <SDL_mixer.h>
#include <iostream>

struct SoundAndChannel
{
    Mix_Chunk* Sound;
    int SoundChannel;
};

class SDLAudioImpl
{
public:
    SDLAudioImpl() : m_Music(nullptr)
	{
        const int maxChannels = 8;
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, maxChannels, 2048);
    }

    ~SDLAudioImpl()
	{
        for (const auto& [id, soundAndChannel] : m_Sounds) 
        {
            Mix_FreeChunk(soundAndChannel.Sound);
        }
        if (m_Music) 
        {
            Mix_FreeMusic(m_Music);
        }
        Mix_CloseAudio();
    }

    void AddSound(const std::string& soundName, int soundChannel, const char* filePathForSound)
	{
        Mix_Chunk* sound = Mix_LoadWAV(filePathForSound);
        m_Sounds.emplace(soundName, SoundAndChannel{ sound, soundChannel });
    }

    void AddMusic(const char* filePathForMusic)
    {
        m_Music = Mix_LoadMUS(filePathForMusic);
    }

    void PlaySound(const std::string& soundName, int loops)
	{
        auto soundAndChannel = m_Sounds.find(soundName)->second;
    	soundAndChannel.SoundChannel = Mix_PlayChannel(soundAndChannel.SoundChannel, soundAndChannel.Sound, loops);
    }

    void PlayMusic(int loops)
    {
        Mix_PlayMusic(m_Music, loops);
    }

    void PauseSound(const std::string& soundName)
	{
        auto soundAndChannel = m_Sounds.find(soundName);
    	Mix_Pause(soundAndChannel->second.SoundChannel);

    }

    void PauseMusic()
    {
        Mix_PauseMusic();
    }

    void PauseAllSounds()
	{
        Mix_Pause(-1);
    }

    void StopSound(const std::string& soundName)
	{
        auto soundAndChannel = m_Sounds.find(soundName);
    	Mix_HaltChannel(soundAndChannel->second.SoundChannel);
    }

    void StopAllSounds()
	{
        Mix_HaltChannel(-1);
    }

private:
    std::unordered_map<std::string, SoundAndChannel> m_Sounds;
    Mix_Music* m_Music;
};

SDLAudio::SDLAudio() : pImpl(std::make_unique<SDLAudioImpl>()) {}

SDLAudio::~SDLAudio() = default;

void SDLAudio::AddSound(std::string soundName, int soundChannel, const char* filePathForSound)
{
    m_EventQueue.emplace([this, soundName, soundChannel, filePathForSound]() {pImpl->AddSound(soundName, soundChannel, filePathForSound);});
}

void SDLAudio::AddMusic(const char* filePathForMusic)
{
    m_EventQueue.emplace([this, filePathForMusic]() {  pImpl->AddMusic(filePathForMusic); });
}

void SDLAudio::PlaySound(std::string soundName, int loops)
{
    m_EventQueue.emplace([this, loops, soundName]() { pImpl->PlaySound(soundName, loops);});
}

void SDLAudio::PlayMusic(int loops)
{
    m_EventQueue.emplace([this, loops]() {  pImpl->PlayMusic(loops); });
}

void SDLAudio::PauseSound(std::string soundName)
{
    m_EventQueue.emplace([this, soundName]() { pImpl->PauseSound(soundName); });
}

void SDLAudio::PauseMusic()
{
    m_EventQueue.emplace([this]() {pImpl->PauseMusic();});
}

void SDLAudio::PauseAllSounds()
{
    m_EventQueue.emplace([this]() { pImpl->PauseAllSounds(); });
}

void SDLAudio::StopSound(std::string soundName)
{
    m_EventQueue.emplace([this, soundName]() {pImpl->StopSound(soundName);});
}

void SDLAudio::StopAllSounds()
{
    m_EventQueue.emplace([this]() {  pImpl->StopAllSounds(); });
}

void SDLAudio::Run()
{
    while (!m_EventQueue.empty())
    {
        auto& func = m_EventQueue.front(); 
        func(); 
        m_EventQueue.pop();
    }
}

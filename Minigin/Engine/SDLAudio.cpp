#include "SDLAudio.h"
#include <unordered_map>
#include <SDL_mixer.h>
#include <iostream>

// Internal structure to hold sound data
struct SoundAndChannel
{
    Mix_Chunk* Sound;
    int SoundChannel;
};

// Implementation class: hides all SDL_mixer details from the header
class SDLAudioImpl
{
public:
    SDLAudioImpl() : m_Music(nullptr)
	{
        // Set your desired audio configuration here
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

    void PlaySound(const std::string& soundName, int loops)
	{
        auto soundAndChannel = m_Sounds.find(soundName)->second;
    	soundAndChannel.SoundChannel = Mix_PlayChannel(soundAndChannel.SoundChannel, soundAndChannel.Sound, loops);
    }

    void PauseSound(const std::string& soundName)
	{
        auto it = m_Sounds.find(soundName);
    	Mix_Pause(it->second.SoundChannel);

    }

    void PauseAllSounds()
	{
        Mix_Pause(-1);
    }

    void StopSound(const std::string& soundName)
	{
        auto it = m_Sounds.find(soundName);
    	Mix_HaltChannel(it->second.SoundChannel);
    }

    void StopAllSounds()
	{
        Mix_HaltChannel(-1);
    }

private:
    std::unordered_map<std::string, SoundAndChannel> m_Sounds;
    Mix_Music* m_Music;
};

// SDLAudio method implementations delegate to SDLAudioImpl

SDLAudio::SDLAudio() : pImpl(std::make_unique<SDLAudioImpl>()) {}

SDLAudio::~SDLAudio() = default;

void SDLAudio::AddSound(std::string soundName, int soundChannel, const char* filePathForSound)
{
    pImpl->AddSound(soundName, soundChannel, filePathForSound);
}

void SDLAudio::PlaySound(std::string soundName, int loops)
{
    pImpl->PlaySound(soundName, loops);
}

void SDLAudio::PauseSound(std::string soundName)
{
    pImpl->PauseSound(soundName);
}

void SDLAudio::PauseAllSounds()
{
    pImpl->PauseAllSounds();
}

void SDLAudio::StopSound(std::string soundName)
{
    pImpl->StopSound(soundName);
}

void SDLAudio::StopAllSounds()
{
    pImpl->StopAllSounds();
}

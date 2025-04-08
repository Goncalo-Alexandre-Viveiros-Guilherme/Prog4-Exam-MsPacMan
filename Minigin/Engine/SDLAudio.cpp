#include "SDLAudio.h"

#include <iostream>
#include <ostream>

#include "SDL.h"
#include "SDL_log.h"

SDLAudio::SDLAudio(): m_Music(nullptr)
{
    const int max_channels = 8;
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, max_channels, 2048);
}

SDLAudio::~SDLAudio()
{
    for (const auto& [id, soundAndChannel] : m_Sounds) 
    {
        Mix_FreeChunk(soundAndChannel.Sound);
    }
    Mix_FreeMusic(m_Music);
    Mix_CloseAudio();
}

void SDLAudio::AddSound(std::string soundName, int soundChannel, const char* filePathForSound) /*Passing -1 to the soundChannel will play the sound on the next available channel*/
{
    m_Sounds.emplace(soundName, SoundAndChannel(Mix_LoadWAV(filePathForSound), soundChannel));
}

void SDLAudio::PlaySound(std::string soundName, int loops)
{
    auto it = m_Sounds.find(soundName);
    if (it != m_Sounds.end()) 
    {
        auto& soundAndChannel = it->second;

        // Check if the sound is valid
        if (soundAndChannel.Sound != nullptr) 
        {
            soundAndChannel.SoundChannel = Mix_PlayChannel(soundAndChannel.SoundChannel, soundAndChannel.Sound, loops);
        }
        else 
        {
            std::cerr << "Sound is invalid: " << soundName << std::endl;
        }
    }

    else 
    {
        std::cerr << "Sound not found: " << soundName << std::endl;
    }
    //
}

void SDLAudio::PauseSound(std::string soundName)
{
    Mix_Pause(m_Sounds.find(soundName)->second.SoundChannel);
}

void SDLAudio::PauseAllSounds()
{
    Mix_Pause(-1);
}

void SDLAudio::StopSound(std::string soundName)
{
    Mix_HaltChannel(m_Sounds.find(soundName)->second.SoundChannel);
}

void SDLAudio::StopAllSounds()
{
    Mix_HaltChannel(-1);
}
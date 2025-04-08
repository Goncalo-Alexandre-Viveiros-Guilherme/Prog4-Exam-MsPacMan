#include "SDLAudio.h"

#include <iostream>
#include <ostream>

#include "SDL.h"
#include "SDL_log.h"

SDLAudio::SDLAudio(): m_Music(nullptr)
{
    int flags = MIX_INIT_MP3 | MIX_INIT_OGG;
    int initted = Mix_Init(flags);

    if ((initted & flags) != flags)
    {
        std::cerr << "Mix_Init: Failed to init requested audio support!\n";
        std::cerr << "Mix_Init error: " << Mix_GetError() << std::endl;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cerr << "Mix_OpenAudio failed: " << Mix_GetError() << std::endl;
    }

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 8, 2048);

    int sint = Mix_Init(0);
}

SDLAudio::~SDLAudio()
{

    for (const auto& [id, chunk] : m_Sounds) 
    {
        Mix_FreeChunk(chunk);
    }
    Mix_FreeMusic(m_Music);
    Mix_CloseAudio();
}

void SDLAudio::PlaySound(int soundID)
{
    Mix_Chunk* sound = Mix_LoadWAV("boom.wav");
    Mix_Music* music = Mix_LoadMUS("skibidi.ogg");

    //Mix_PlayChannel(-1, sound, -1); // -1 = pick first available, 0 = no loop
    Mix_PlayMusic(music, -1);      // -1 = loop forever
}

void SDLAudio::PauseSound(int soundID)
{
    // Implementation to pause a specific sound
    Mix_Pause(soundID);
}

void SDLAudio::PauseAllSounds()
{
    // Implementation to pause all sounds
    Mix_Pause(-1);
}

void SDLAudio::StopSound(int soundID)
{
    // Implementation to stop a specific sound
    Mix_HaltChannel(soundID);
}

void SDLAudio::StopAllSounds()
{
    // Implementation to stop all sounds
    Mix_HaltChannel(-1);
}
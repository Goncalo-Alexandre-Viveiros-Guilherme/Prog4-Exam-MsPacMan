#pragma once

#include <map>
#include <string>

#include "Audio.h"
#include "SDL_mixer.h"

class SDLAudio final : public Audio
{
public:
SDLAudio();
~SDLAudio() override;
void PlaySound(int soundID) override;
void PauseSound(int soundID) override; 
void PauseAllSounds() override; 
void StopSound(int soundID) override; 
void StopAllSounds() override; 

private:
std::map<std::string, int> m_SoundIDs;
std::map<int, Mix_Chunk*> m_Sounds;
Mix_Music* m_Music;
};
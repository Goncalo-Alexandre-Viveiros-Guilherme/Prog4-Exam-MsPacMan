#pragma once

#include <unordered_map>

#include "Audio.h"
#include "SDL_mixer.h"

struct SoundAndChannel
{
	Mix_Chunk* Sound;
	int SoundChannel;
};

class SDLAudio final : public Audio
{
	public:
	SDLAudio();
	~SDLAudio() override;
	void AddSound(std::string soundName,int soundChannel, const char* filePathForSound) override;
	void PlaySound(std::string soundName,int loops) override;
	void PauseSound(std::string soundName) override;
	void PauseAllSounds() override; 
	void StopSound(std::string soundName) override;
	void StopAllSounds() override; 
	
	private:
	std::unordered_map<std::string, SoundAndChannel> m_Sounds;
	Mix_Music* m_Music;
};
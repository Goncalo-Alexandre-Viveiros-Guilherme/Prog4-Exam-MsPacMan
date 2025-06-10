#pragma once
#include <string>

class Audio
{
public:
	virtual ~Audio() {}
	virtual void AddSound(std::string soundName, int soundChannel, const char* filePathForSound) = 0;
	virtual void AddMusic(const std::string& musicName, const char* filePathForMusic) = 0;

	virtual void PlaySound(std::string soundName, int volume = 100, int loops = 0) = 0;
	virtual void PlayMusic(const std::string& musicName, int volume = 100, int loops = 0) = 0;

	virtual void PauseSound(std::string soundName) = 0;
	virtual void PauseMusic() = 0;
	virtual void PauseAllSounds() = 0;

	virtual void StopSound(std::string soundName) = 0;
	virtual void StopAllSounds() = 0;

	virtual void SetAllAudioVolume(int volume) = 0;
	virtual void SetChannelVolume(int channel, int volume) = 0;
	virtual void SetSoundVolume(std::string soundName, int volume) = 0;
	virtual void SetMusicVolume(int volume) = 0;
};
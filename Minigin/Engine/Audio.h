#pragma once

class Audio
{
public:
	virtual ~Audio() {}
	virtual void PlaySound(int soundID) = 0;
	virtual void PauseSound(int soundID) = 0;
	virtual void PauseAllSounds() = 0;
	virtual void StopSound(int soundID) = 0;
	virtual void StopAllSounds() = 0;
};
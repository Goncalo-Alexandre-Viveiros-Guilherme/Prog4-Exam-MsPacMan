#pragma once

#include "Audio.h"


class NullAudio final : public Audio
{
public:
	virtual ~NullAudio() {}
	virtual void PlaySound(int soundID) override { soundID = 0; }
	virtual void PauseSound(int soundID) override { soundID = 0; }
	virtual void PauseAllSounds() override {}
	virtual void StopSound(int soundID) override { soundID = 0; }
	virtual void StopAllSounds() override {}
};
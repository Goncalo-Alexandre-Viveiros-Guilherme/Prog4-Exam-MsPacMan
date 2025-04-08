#pragma once

#include "NullAudio.h"

class ServiceLocator
{
public:
	static Audio& GetAudio() { return *m_AudioService; }
	static void ProvideAudio(Audio* service);

private:
	static Audio* m_AudioService;
	static NullAudio m_NullAudioService;
};
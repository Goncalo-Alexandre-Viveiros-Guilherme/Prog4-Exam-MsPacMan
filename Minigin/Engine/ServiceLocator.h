#pragma once

#include <memory>
#include <Audio.h>

class ServiceLocator
{
public:
	static Audio& GetAudio() { return *m_AudioService; }
	static void ProvideAudio(std::unique_ptr<Audio>&& service);

private:
	static std::unique_ptr<Audio> m_AudioService;
};
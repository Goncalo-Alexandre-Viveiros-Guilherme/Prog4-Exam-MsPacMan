#include "ServiceLocator.h"

#include <cassert>
#include "SDLAudio.h"

std::unique_ptr<Audio> ServiceLocator::m_AudioService = nullptr;

void ServiceLocator::ProvideAudio(std::unique_ptr<Audio>&& service)
{
	if (service == nullptr)
	{
		assert("Provided Audio System is null or not valid");
	}
    m_AudioService = std::move(service);
}
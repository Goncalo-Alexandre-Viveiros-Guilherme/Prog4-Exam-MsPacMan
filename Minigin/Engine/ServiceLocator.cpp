#include "ServiceLocator.h"

#include <cassert>
#include "SDLAudioService.h"

std::unique_ptr<Audio> ServiceLocator::m_AudioService = nullptr;
std::unique_ptr<CollisionService> ServiceLocator::m_CollisionService = nullptr;

void ServiceLocator::ProvideAudioService(std::unique_ptr<Audio>&& service)
{
	assert(service && "Provided Audio System is null or not valid");

    m_AudioService = std::move(service);
}

void ServiceLocator::ProvideCollisionService(std::unique_ptr<CollisionService>&& service)
{
	assert(service && "Provided Collision System is null or not valid");
	
	m_CollisionService = std::move(service);
}

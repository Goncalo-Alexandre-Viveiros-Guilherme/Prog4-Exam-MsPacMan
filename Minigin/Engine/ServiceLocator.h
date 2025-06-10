#ifndef SERVICELOCATOR_H
#define SERVICELOCATOR_H
#include <memory>
#include "AudioService.h"
#include "CollisionService.h"

class ServiceLocator
{
public:
	static Audio& GetAudioService() { return *m_AudioService; }
	static void ProvideAudioService(std::unique_ptr<Audio>&& service);

	static CollisionService& GetCollisionService() { return *m_CollisionService; }
	static void ProvideCollisionService(std::unique_ptr<CollisionService>&& service);

private:
	static std::unique_ptr<Audio> m_AudioService;
	static std::unique_ptr<CollisionService> m_CollisionService;
};
#endif // SERVICELOCATOR_H

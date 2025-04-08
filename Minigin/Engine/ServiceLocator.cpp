#include "ServiceLocator.h"

std::unique_ptr<Audio> ServiceLocator::m_AudioService = nullptr;

void ServiceLocator::ProvideAudio(std::unique_ptr<Audio>&& service)
{
    m_AudioService = std::move(service);
}
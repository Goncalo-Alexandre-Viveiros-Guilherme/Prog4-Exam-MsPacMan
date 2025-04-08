#include "ServiceLocator.h"

void ServiceLocator::ProvideAudio(Audio* service)
{
    if (service == nullptr)
    {
        m_AudioService = &m_NullAudioService;
    }
    else
    {
        m_AudioService = service;
    }
}

NullAudio ServiceLocator::m_NullAudioService;
Audio* ServiceLocator::m_AudioService = &m_NullAudioService;
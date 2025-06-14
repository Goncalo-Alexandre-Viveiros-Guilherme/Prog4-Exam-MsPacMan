#include "HealthComponent.h"

#include "EventDispatcher.h"
#include "Events.h"
#include "HealthDisplayComponent.h"
#include "InputManager.h"
#include "MsPacmanCode.h"

HealthComponent::HealthComponent(dae::GameObject* parent, float maxHealth) :Component(parent), m_MaxHealth(maxHealth), m_Health(maxHealth)
{
}

void HealthComponent::AddToHealth(float value)
{
    m_Health = m_Health + value;
    HealthChangedEvent event(m_Health);
    EventDispatcher::GetInstance().Dispatch(event, GetParent());

    if (m_Health == 0)
    {
        MsPacmanCode::MainMenuScene();
    }
}

float HealthComponent::GetHealth() const
{
    return m_Health;
}
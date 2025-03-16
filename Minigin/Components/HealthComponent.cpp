#include "HealthComponent.h"

#include <algorithm>

#include "EventDispatcher.h"
#include "HealthDisplayComponent.h"

HealthComponent::HealthComponent(dae::GameObject& parent, float maxHealth):Component(parent), m_MaxHealth(maxHealth),m_Health(maxHealth)
{

}

void HealthComponent::AddToHealth(float value)
{
    m_Health = m_Health + value;
    HealthChangedEvent event(m_Health,this);
    EventDispatcher::GetInstance().Dispatch(event);
}

float HealthComponent::GetHealth() const
{
	return m_Health;
}

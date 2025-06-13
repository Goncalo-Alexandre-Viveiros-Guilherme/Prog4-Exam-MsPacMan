#include "HealthComponent.h"

#include "EventDispatcher.h"
#include "Events.h"
#include "HealthDisplayComponent.h"
#include "MsPacmanCode.h"

HealthComponent::HealthComponent(dae::GameObject* parent, float maxHealth) :Component(parent), m_MaxHealth(maxHealth), m_Health(maxHealth)
{
    EventDispatcher::GetInstance().AddListener<ResetEntityPosEvent>
        (nullptr, [this](const ResetEntityPosEvent& event)
            {
                AddToHealth(-1);
                event;
            }
        );
}

void HealthComponent::AddToHealth(float value)
{
    m_Health = m_Health + value;
    HealthChangedEvent event(m_Health);
    EventDispatcher::GetInstance().Dispatch(event, GetParent());

    if (m_Health == 0)
    {
        MsPacmanCode msPacmanCode{ GameModes::Normal, };
        msPacmanCode.LoadGameCode("level1.csv");
    }
}

float HealthComponent::GetHealth() const
{
    return m_Health;
}
#pragma once
#include "Component.h"
#include "EventDispatcher.h"

class HealthComponent : public Component, public Event
{
public:
    HealthComponent(dae::GameObject* parent, float maxHealth);

    void AddToHealth(float value);
    float GetHealth() const;

private:
    float m_MaxHealth;
    float m_Health;
};
#pragma once
#include <map>

#include "EventDispatcher.h"
#include "FSM.h"

namespace dae
{
	class Scene;
}

class PointsComponent;
class HealthComponent;


class HealthChangedEvent : public Event 
{
public:
    HealthChangedEvent(float newHealth):
	m_NewHealth(newHealth){}

    float m_NewHealth;
};

class PointsChangedEvent : public Event
{
public:
    PointsChangedEvent(float newPointAmount) : m_Points(newPointAmount)
	{}

    float m_Points;
};

class AddPointsEvent : public Event
{
public:
	AddPointsEvent(float amountToAdd): m_AmountToAdd(amountToAdd)
	{
	}

	float m_AmountToAdd{};
};

class DestroyGameObjectEvent : public Event
{
public:
	DestroyGameObjectEvent(dae::GameObject* gameObjectToDestroy) : m_GameObjDestroy(gameObjectToDestroy)
	{
	}

	dae::GameObject* m_GameObjDestroy{};
};


class ResetEntityPosEvent : public Event
{
public:
	ResetEntityPosEvent()
	{
	}

};

class EdibleGhostsEvent : public Event
{
public:
	EdibleGhostsEvent()
	{
	}

};

template <typename EventType>
class EventCondition : public FSM::Condition {
public:
    EventCondition(dae::GameObject* listener) : m_Listener(listener) {
        EventDispatcher::GetInstance().AddListener<EventType>(
            m_Listener,
            [this](const EventType&) { m_Triggered = true; }
        );
    }

    bool Evaluate() const override {
        if (m_Triggered) {
            m_Triggered = false;
            return true;
        }
        return false;
    }

private:
    dae::GameObject* m_Listener;
    mutable bool m_Triggered = false;
};

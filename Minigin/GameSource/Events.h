#pragma once
#include "EventDispatcher.h"

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


namespace FSM
{
	enum States
	{
		NullStarterState,
		MovingState
	};
	class NewState : public Event
	{
	public:
		NewState(States newState): m_NewState(newState)
		{}

		States m_NewState;
	};

};
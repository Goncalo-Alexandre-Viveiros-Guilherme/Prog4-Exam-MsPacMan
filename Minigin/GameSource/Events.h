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
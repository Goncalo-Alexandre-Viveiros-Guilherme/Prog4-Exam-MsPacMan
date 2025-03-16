#pragma once

class PointsComponent;
class HealthComponent;

class Event
{
public:
    virtual ~Event() = default;
};


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
    PointsChangedEvent(float newPointAmount) :
        m_Points(newPointAmount){}

    float m_Points;
};

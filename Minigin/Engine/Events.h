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
    HealthChangedEvent(float newHealth,HealthComponent* healthComponent):
	m_NewHealth(newHealth), m_HealthComponent(healthComponent){}

    float m_NewHealth;
    HealthComponent* m_HealthComponent;
};

class PointsChangedEvent : public Event
{
public:
    PointsChangedEvent(float newPointAmount, PointsComponent* pointsComponent) :
        m_Points(newPointAmount), m_PointsComponent(pointsComponent) {}

    float m_Points;
    PointsComponent* m_PointsComponent;
};

class PlayerAchievementsEvent: public Event
{
public:
    PlayerAchievementsEvent(dae::GameObject* gameObject) :
	 m_GameObject(gameObject) {}

    dae::GameObject* m_GameObject;
};
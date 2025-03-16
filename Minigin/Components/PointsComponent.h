#pragma once
#include "Component.h"
#include "Events.h"

class PointsComponent : public Component, public Event
{
public:
    PointsComponent(dae::GameObject& parent);

    void AddToPoints(float value);
    float GetPoints() const;

private:
    float m_CurrentPoints;
};
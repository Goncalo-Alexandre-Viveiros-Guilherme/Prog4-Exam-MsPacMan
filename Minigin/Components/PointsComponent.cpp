#include "PointsComponent.h"
#include "EventDispatcher.h"
#include "SteamAchievements.h"

PointsComponent::PointsComponent(dae::GameObject& parent): Component(parent), m_CurrentPoints(0)
{
}

void PointsComponent::AddToPoints(const float value)
{
	m_CurrentPoints += value;
	PointsChangedEvent event(m_CurrentPoints);
	EventDispatcher::GetInstance().Dispatch(event,GetParent());
}

float PointsComponent::GetPoints() const
{
	return m_CurrentPoints;
}

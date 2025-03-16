#include "PointsComponent.h"
#include "EventDispatcher.h"
#include "SteamAchievements.h"

PointsComponent::PointsComponent(dae::GameObject& parent): Component(parent), m_CurrentPoints(0)
{
}

void PointsComponent::AddToPoints(const float value)
{
	m_CurrentPoints += value;
	PointsChangedEvent event(m_CurrentPoints, this);
	EventDispatcher::GetInstance().Dispatch(event);

	if (m_CurrentPoints >= 500)
	{
		if (g_SteamAchievements)
			g_SteamAchievements->SetAchievement("ACH_WIN_ONE_GAME");
	}
}

float PointsComponent::GetPoints() const
{
	return m_CurrentPoints;
}

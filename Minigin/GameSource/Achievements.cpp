#include "Achievements.h"
#include "SteamAchievements.h"

void Achievements::NotifyAchievements() const
{
	EventDispatcher::GetInstance().AddListener<PointsChangedEvent>
		(nullptr, [this](const PointsChangedEvent& event)
			{
				PointAchievements(event.m_Points);
			}
		);
}

void Achievements::PointAchievements(float points)
{
	if (!g_SteamAchievements) return;

	if (points >= 500)
	{
		g_SteamAchievements->SetAchievement("ACH_WIN_ONE_GAME");
	}

	if (points >= 1000)
	{
		g_SteamAchievements->SetAchievement("ACH_WIN_100_GAMES");
	}

}

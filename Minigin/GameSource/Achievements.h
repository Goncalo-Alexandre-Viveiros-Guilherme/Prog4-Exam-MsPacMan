#pragma once
#include "EventDispatcher.h"

class Achievements : public dae::Singleton<Achievements>
{
	friend class Singleton;
public:
	void NotifyAchievements() const;

private:

	static void PointAchievements(float points);

};
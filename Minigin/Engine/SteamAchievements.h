#pragma once
#include <memory>

#include "steam_api_common.h"
#include "isteamuserstats.h"

struct Achievement_t
{
	int m_eAchievementID;
	const char* m_pchAchievementID;
	char m_rgchName[128];
	char m_rgchDescription[256];
	bool m_bAchieved;
	int m_iIconImage;
};

class CSteamAchievements
{
private:
	uint64 m_iAppID;
	Achievement_t* m_pAchievements;
	int m_iNumAchievements;
	bool m_bInitialized;

public:
	CSteamAchievements(Achievement_t* Achievements, int NumAchievements);
	~CSteamAchievements();

	bool RequestStats();
	bool SetAchievement(const char* ID);

	STEAM_CALLBACK(CSteamAchievements, OnUserStatsReceived, UserStatsReceived_t,
		m_CallbackUserStatsReceived);
	STEAM_CALLBACK(CSteamAchievements, OnUserStatsStored, UserStatsStored_t,
		m_CallbackUserStatsStored);
	STEAM_CALLBACK(CSteamAchievements, OnAchievementStored,
		UserAchievementStored_t, m_CallbackAchievementStored);
};

enum EAchievements
{
	ACH_WIN_ONE_GAME = 0,
	ACH_WIN_100_GAMES = 1,
	ACH_TRAVEL_FAR_ACCUM = 2,
	ACH_TRAVEL_FAR_SINGLE = 3,
};

// Declare but do not define the global variables in the header file
extern Achievement_t g_Achievements[];
extern std::unique_ptr<CSteamAchievements> g_SteamAchievements;

#ifndef WINCONDITIONMANAGER_H
#define WINCONDITIONMANAGER_H

#include "Events.h"
#include "Singleton.h"
#include "GameObject.h"
#include <MsPacmanCode.h>
#include <memory>

class WinConditionManager : public dae::Singleton<WinConditionManager>
{
public:
    void Init();
    ~WinConditionManager() override = default;

    void SetWinConditions(int totalDots);
    void SetCurrentGameMode(GameModes currentGameMode);
    void SetCurrentLevel(int level);

    void NextLevel();


private:
    friend class Singleton<WinConditionManager>;
    WinConditionManager();

    void OnDotEaten();
    void CheckWinConditions();

    GameModes m_CurrentGameMode;
    int m_TotalDots = 0;
    int m_DotsEaten = 0;
    int m_CurrentLevel = 0; // Default to level 1
    bool m_Initialized = false;
};

#endif // WINCONDITIONMANAGER_H
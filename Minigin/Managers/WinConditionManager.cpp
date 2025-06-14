#include "WinConditionManager.h"

WinConditionManager::WinConditionManager() = default;

void WinConditionManager::Init()
{
    if (m_Initialized) return;

    EventDispatcher::GetInstance().AddListener<PelletEaten>(
        nullptr,
        [this](const PelletEaten&) { OnDotEaten(); }
    );

    m_Initialized = true;
}

void WinConditionManager::SetWinConditions(int totalDots) {
    m_TotalDots = totalDots;
    m_DotsEaten = 0;
}

void WinConditionManager::SetCurrentGameMode(GameModes currentGameMode) {
    m_CurrentGameMode = currentGameMode;
}

void WinConditionManager::SetCurrentLevel(int level) {
    m_CurrentLevel = level;
}

void WinConditionManager::NextLevel()
{
    m_CurrentLevel += 1;
    if (m_CurrentLevel > 2) return;

    std::string wallTexture;
    switch (m_CurrentLevel) {
    case 1: wallTexture = "WallsTransparent1.png"; break;
    case 2: wallTexture = "WallsTransparent2.png"; break;
    default: wallTexture = "WallsDefault.png";
    }

    m_TotalDots = 0;
    m_DotsEaten = 0;

    MsPacmanCode msPacmanCode{ m_CurrentGameMode };
    msPacmanCode.LoadGameCode("level1.csv", wallTexture);
}

void WinConditionManager::OnDotEaten() {
    m_DotsEaten++;
    CheckWinConditions();
}

void WinConditionManager::CheckWinConditions()
{
    if (m_DotsEaten < m_TotalDots) return;

    m_CurrentLevel += 1;

    std::string wallTexture;
    switch (m_CurrentLevel) {
    case 1: wallTexture = "WallsTransparent1.png"; break;
    case 2: wallTexture = "WallsTransparent2.png"; break;
    default: wallTexture = "WallsDefault.png";
    }

    m_TotalDots = 0;
    m_DotsEaten = 0;

    MsPacmanCode msPacmanCode{ m_CurrentGameMode };
    msPacmanCode.LoadGameCode("level1.csv", wallTexture);
}
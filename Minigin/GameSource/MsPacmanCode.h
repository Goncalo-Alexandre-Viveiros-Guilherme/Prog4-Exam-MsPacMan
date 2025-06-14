#pragma once
#include <functional>
#include <unordered_map>

#include "Scene.h"
#include "vec2.hpp"

class Ghost;

enum GameModes
{
	Normal,
	CoOp,
	Versus
};

class MsPacmanCode
{
public:
	MsPacmanCode(GameModes gameMode);
	~MsPacmanCode();

	void InitializeResources(const std::string& fileName);
	void LoadGameCode(const std::string& fileName, const std::string& wallPngFilePath);
	void AddWall(dae::Scene* scene, int posX, int posY, int srcX, int srcY, int wallType, float rotation);
	void InitSpawnMap();
	void ParseCSVAndSpawn(const std::string& filepath, dae::Scene* scene);

	static void MainMenuScene();

private:
	//dae::Scene* m_pScene;
	using SpawnFunc = std::function<void(dae::Scene* scene, int gridX, int gridY, float rotation)>;
	std::unordered_map<std::string, SpawnFunc> m_SpawnMap;
	float m_MapScalingFactor {3};
	GameModes m_GameMode;
	dae::Scene* m_Scene;
	std::string m_WallPath;
	std::vector<std::unique_ptr<Ghost>> m_Ghosts;
	std::vector <glm::vec2> m_ForbiddenCells;
	int m_AmountOfPellets {0};
};

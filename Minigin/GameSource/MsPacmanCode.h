#pragma once
#include <functional>
#include <unordered_map>

#include "Scene.h"

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
	void LoadGameCode(const std::string& fileName);
	void AddWall(dae::Scene* scene, int posX, int posY, int srcX, int srcY, int wallType, float rotation);
	void InitSpawnMap();
	void ParseCSVAndSpawn(const std::string& filepath, dae::Scene* scene);

private:
	//dae::Scene* m_pScene;
	using SpawnFunc = std::function<void(dae::Scene* scene, int gridX, int gridY, float rotation)>;
	std::unordered_map<std::string, SpawnFunc> m_SpawnMap;
	float m_MapScalingFactor {3};
	GameModes m_GameMode;
	dae::Scene* m_Scene;
	std::vector<std::unique_ptr<Ghost>> m_Ghosts;
};

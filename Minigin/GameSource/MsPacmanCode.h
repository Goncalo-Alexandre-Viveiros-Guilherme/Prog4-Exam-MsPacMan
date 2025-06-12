#pragma once
#include <functional>
#include <unordered_map>

#include "Scene.h"

class MsPacmanCode
{
public:
	MsPacmanCode();
	~MsPacmanCode() = default;

	void InitializeResources();
	void LoadGameCode();
	void AddWall(dae::Scene& scene, int posX, int posY, int srcX, int srcY, int wallType, float rotation);
	void InitSpawnMap();
	void ParseCSVAndSpawn(const std::string& filepath, dae::Scene& scene);

private:
	//dae::Scene* m_pScene;
	using SpawnFunc = std::function<void(dae::Scene& scene, int gridX, int gridY, float rotation)>;
	std::unordered_map<std::string, SpawnFunc> m_SpawnMap;
	float m_MapScalingFactor {3};
};

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
	static void AddWall(dae::Scene& scene, int posX, int posY, int srcX, int srcY);
	void InitSpawnMap();
	void ParseCSVAndSpawn(const std::string& filepath, dae::Scene& scene);

private:
	//dae::Scene* m_pScene;
	using SpawnFunc = std::function<void(dae::Scene& scene, int gridX, int gridY)>;
	std::unordered_map<int, SpawnFunc> m_SpawnMap;
};

#pragma once
#include "Scene.h"

class MsPacmanCode
{
public:
	MsPacmanCode() = delete;
	~MsPacmanCode() = default;

	static void InitializeResources();
	static void LoadGameCode();
private:
	dae::Scene m_Scene;
};

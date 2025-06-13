#pragma once

#include "Component.h"
#include <imgui.h>
#include <vector>

struct Transform
{
	float matrix[16] = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1 };
};

class GameObject3D
{
public:
	Transform transform;
	int ID;
};

class GameObject3DAlt
{
public:
	Transform* transform;
	int ID;
};

class GraphCacheComponent final : public Component
{
public:
	GraphCacheComponent(dae::GameObject* parent);
	
	void Update() override;
	void Render() override;

	void RunSampleEx2();
	void RunSampleEx3();
	void RunSampleEx3Alt();
	void KeepSamplePositive();

private:
	int* m_SampleAmountEx2 = new int{ 1 };
	int* m_SampleAmountEx3 = new int{ 1 };

	bool m_DisplayGraphEx2{ false };
	bool m_DisplayGraphEx3{ false };
	bool m_DisplayGraphEx3Alt{ false };

	std::vector<int> m_Ex2Durations{};
	std::vector<int> m_Ex3Durations{};
	std::vector<int> m_Ex3DurationsAlt{};
};
#pragma once
#include <memory>
#include <vector>
#include "Events.h"

namespace dae
{
	class Scene;
	class GameObject;
}

class MsPacMan
{
public:
	MsPacMan(dae::Scene& scene);
	~MsPacMan();

	void SwapState(FSM::States newState);
	dae::GameObject* GetGameObject() const;
private:
	std::shared_ptr<dae::GameObject> m_MainGameObject;
	FSM::States m_CurrentState;
	std::vector<FSM::States> m_States;
};

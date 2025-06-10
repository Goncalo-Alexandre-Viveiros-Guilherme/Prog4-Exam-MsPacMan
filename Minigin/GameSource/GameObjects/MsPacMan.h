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
	~MsPacMan() = default;

	dae::GameObject* GetGameObject() const;
private:
	std::shared_ptr<dae::GameObject> m_MainGameObject;
};

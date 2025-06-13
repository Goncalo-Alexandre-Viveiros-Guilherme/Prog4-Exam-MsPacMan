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
	MsPacMan(const dae::Scene* scene, const glm::vec3 originalPos);
	~MsPacMan() = default;

	dae::GameObject* GetGameObject() const;

private:
	dae::GameObject* m_MainGameObject;
};

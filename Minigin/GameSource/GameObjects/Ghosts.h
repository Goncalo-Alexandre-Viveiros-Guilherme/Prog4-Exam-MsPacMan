#ifndef GHOSTS_H
#define GHOSTS_H

#include <memory>
#include <string>

#include "FSM.h"
#include "vec3.hpp"

class FSMComponent;

namespace dae
{
	class Scene;
	class GameObject;
}

class Ghost
{
public:
	Ghost(dae::Scene* scene, const std::string& ghostName,const glm::vec3 originalPos);
	virtual ~Ghost() = default;

	dae::GameObject* GetGameObject() const;

	virtual void InitializeFSM(dae::Scene* scene) = 0;

protected:
	dae::GameObject* m_MainGameObject	{nullptr};
	FSMComponent* m_FSMComponent		{nullptr};
	FSM::State* m_NullState				{nullptr};
};

class Blinky : public Ghost
{
public:
	Blinky(dae::Scene* scene, const glm::vec3 originalPos);
	~Blinky() override = default;

	void InitializeFSM(dae::Scene* scene) override;
};

class PlayerBlinky
{
public:
	PlayerBlinky(dae::Scene* scene, const glm::vec3 originalPos);
	~PlayerBlinky() = default;


private:
	dae::GameObject* m_MainGameObject{ nullptr };
};

class Pinky : public Ghost
{
public:
	Pinky(dae::Scene* scene, const glm::vec3 originalPos);
	~Pinky() override = default;

	void InitializeFSM(dae::Scene* scene) override;
};

class Inky : public Ghost
{
public:
	Inky(dae::Scene* scene, const glm::vec3 originalPos);
	~Inky() override = default;

	void InitializeFSM(dae::Scene* scene) override;
};

class Clyde : public Ghost
{
public:
	Clyde(dae::Scene* scene, const glm::vec3 originalPos);
	~Clyde() override = default;

	void InitializeFSM(dae::Scene* scene) override;
};

#endif // GHOSTS_H

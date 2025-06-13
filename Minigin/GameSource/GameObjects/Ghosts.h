#ifndef GHOSTS_H
#define GHOSTS_H

#include <memory>
#include <string>

#include "FSM.h"

class FSMComponent;

namespace dae
{
	class Scene;
	class GameObject;
}

class Ghost
{
public:
	Ghost(dae::Scene& scene, const std::string& ghostName);
	virtual ~Ghost() = default;

	dae::GameObject* GetGameObject() const;

	virtual void InitializeFSM(dae::Scene& scene) = 0;
protected:
	dae::GameObject* m_MainGameObject;
	FSMComponent* m_FSMComponent;
	FSM::State* m_NullState;
};

class Blinky : public Ghost
{
public:
	Blinky(dae::Scene& scene);
	~Blinky() override = default;

	void InitializeFSM(dae::Scene& scene) override;
};

class Pinky : public Ghost
{
public:
	Pinky(dae::Scene& scene);
	~Pinky() override = default;

	void InitializeFSM(dae::Scene& scene) override;
};

class Inky : public Ghost
{
public:
	Inky(dae::Scene& scene);
	~Inky() override = default;

	void InitializeFSM(dae::Scene& scene) override;
};

class Clyde : public Ghost
{
public:
	Clyde(dae::Scene& scene);
	~Clyde() override = default;

	void InitializeFSM(dae::Scene& scene) override;
};

#endif // GHOSTS_H

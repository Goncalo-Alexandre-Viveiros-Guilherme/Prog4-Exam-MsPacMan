#include "Ghosts.h"

#include "BoxColliderComponent.h"
#include "FSMComponent.h"
#include "GhostStates.h"
#include "MoveComponent.h"
#include "Scene.h"
#include "SDL_rect.h"
#include "SpriteComponent.h"
#include "vec2.hpp"



Ghost::Ghost(dae::Scene& scene, const std::string& ghostName)
{
	auto obj = std::make_unique<dae::GameObject>(ghostName);

	m_MainGameObject = obj.get();

	scene.Add(std::move<>(obj));
	auto singleGridSize = glm::vec2{ 8 * 3, 8 * 3 };

	m_MainGameObject->AddComponent<BoxColliderComponent>(false, false, 8.f * 3.0f, 8.f * 3.f);
	m_MainGameObject->AddComponent<MoveComponent>(singleGridSize)->SetSpeed(160);

	auto initialState = std::make_unique<FSM::NullState>();

	m_NullState = initialState.get();

	m_FSMComponent = m_MainGameObject->AddComponent<FSMComponent>(std::move<>(initialState));
}

dae::GameObject* Ghost::GetGameObject() const
{
	return m_MainGameObject;
}


Blinky::Blinky(dae::Scene& scene): Ghost(scene,"Blinky")
{
	SDL_Rect srcRect{ 0,0,16,16 };
	m_MainGameObject->AddComponent<SpriteComponent>("Blinky.png", srcRect);
	m_MainGameObject->GetComponent<SpriteComponent>()->SetScale(2.f, 2.f);
}

void Blinky::InitializeFSM(dae::Scene& scene)
{
	auto blinkChaseState = std::make_unique<FSM::BlinkyChaseState>(m_MainGameObject, scene.GetGameObjectByName("MsPacMan"));

	//auto blinkChaseStatePtr = blinkChaseState.get();

	m_FSMComponent->AddTransition(m_NullState, std::move<>(blinkChaseState), std::make_unique<FSM::AlwaysTrueCond>());
}

Pinky::Pinky(dae::Scene& scene): Ghost(scene,"Pinky")
{
	SDL_Rect srcRect{ 0,0,16,16 };
	m_MainGameObject->AddComponent<SpriteComponent>("Pinky.png", srcRect);
	m_MainGameObject->GetComponent<SpriteComponent>()->SetScale(2.f, 2.f);
}

void Pinky::InitializeFSM(dae::Scene& scene)
{
	scene;
}

Inky::Inky(dae::Scene& scene) : Ghost(scene, "Inky")
{
	SDL_Rect srcRect{ 0,0,16,16 };
	m_MainGameObject->AddComponent<SpriteComponent>("Inky.png", srcRect);
	m_MainGameObject->GetComponent<SpriteComponent>()->SetScale(2.f, 2.f);
}

void Inky::InitializeFSM(dae::Scene& scene)
{
	scene;
}

Clyde::Clyde(dae::Scene& scene) : Ghost(scene, "Clyde")
{
	SDL_Rect srcRect{ 0,0,16,16 };
	m_MainGameObject->AddComponent<SpriteComponent>("Clyde.png", srcRect);
	m_MainGameObject->GetComponent<SpriteComponent>()->SetScale(2.f, 2.f);
}

void Clyde::InitializeFSM(dae::Scene& scene)
{
	scene;
}

#include "Ghosts.h"

#include "BoxColliderComponent.h"
#include "Events.h"
#include "FSMComponent.h"
#include "GhostStates.h"
#include "InputManager.h"
#include "MoveComponent.h"
#include "Scene.h"
#include "SDL_rect.h"
#include "SpriteComponent.h"
#include "vec2.hpp"
#include <ResetPositionComponent.h>



Ghost::Ghost(dae::Scene* scene, const std::string& ghostName, const glm::vec3 originalPos)
{
	auto obj = std::make_unique<dae::GameObject>(ghostName);

	m_MainGameObject = obj.get();

	m_MainGameObject->SetLocalPosition(originalPos);
	m_MainGameObject->AddComponent<ResetPositionComponent>(originalPos);

	scene->Add(std::move<>(obj));
	auto singleGridSize = glm::vec2{ 8 * 3, 8 * 3 };

	auto boxColliderComp = m_MainGameObject->AddComponent<BoxColliderComponent>(false, false, 8.f * 3.0f, 8.f * 3.f);
	m_MainGameObject->AddComponent<MoveComponent>(singleGridSize)->SetSpeed(160);

	boxColliderComp->AddOnEnterEvent(std::make_unique<ResetEntityPosEvent>());

	auto initialState = std::make_unique<FSM::NullState>();

	m_NullState = initialState.get();

	m_FSMComponent = m_MainGameObject->AddComponent<FSMComponent>(std::move<>(initialState));
}

dae::GameObject* Ghost::GetGameObject() const
{
	return m_MainGameObject;
}


Blinky::Blinky(dae::Scene* scene, const glm::vec3 originalPos): Ghost(scene,"Blinky",originalPos)
{
	SDL_Rect srcRect{ 0,0,16,16 };
	m_MainGameObject->AddComponent<SpriteComponent>("Blinky.png", srcRect);
	m_MainGameObject->GetComponent<SpriteComponent>()->SetScale(2.f, 2.f);
}

void Blinky::InitializeFSM(dae::Scene* scene)
{
	auto blinkChaseState = std::make_unique<FSM::BlinkyChaseState>(m_MainGameObject, scene->GetGameObjectByName("MsPacMan"));

	//auto blinkChaseStatePtr = blinkChaseState.get();

	m_FSMComponent->AddTransition(m_NullState, std::move<>(blinkChaseState), std::make_unique<FSM::AlwaysTrueCond>());
}

PlayerBlinky::PlayerBlinky(dae::Scene* scene, const glm::vec3 originalPos)
{
	auto obj = std::make_unique<dae::GameObject>("PlayerBlinky");

	m_MainGameObject = obj.get();

	m_MainGameObject->SetLocalPosition(originalPos);
	m_MainGameObject->AddComponent<ResetPositionComponent>(originalPos);

	scene->Add(std::move<>(obj));
	auto singleGridSize = glm::vec2{ 8 * 3, 8 * 3 };

	auto boxColliderComp = m_MainGameObject->AddComponent<BoxColliderComponent>(false, false, 8.f * 3.0f, 8.f * 3.f);
	auto moveComponent = m_MainGameObject->AddComponent<MoveComponent>(singleGridSize);
	moveComponent->SetSpeed(160);

	boxColliderComp->AddOnEnterEvent(std::make_unique<ResetEntityPosEvent>());

	SDL_Rect srcRect{ 0,0,16,16 };
	m_MainGameObject->AddComponent<SpriteComponent>("Blinky.png", srcRect);
	m_MainGameObject->GetComponent<SpriteComponent>()->SetScale(2.f, 2.f);

	auto& inputManager = dae::InputManager::GetInstance();

	inputManager.AddInputMapping<MoveCommand>( {}, {GamePad_DPadUp }, KeyDown, 160.f, DesiredDirection::Up, moveComponent);
	inputManager.AddInputMapping<MoveCommand>( {}, {GamePad_DPadDown }, KeyDown, 160.f, DesiredDirection::Down, moveComponent);
	inputManager.AddInputMapping<MoveCommand>( {}, {GamePad_DPadLeft }, KeyDown, 160.f, DesiredDirection::Left, moveComponent);
	inputManager.AddInputMapping<MoveCommand>( {}, {GamePad_DPadRight}, KeyDown, 160.f, DesiredDirection::Right, moveComponent);
}



Pinky::Pinky(dae::Scene* scene, const glm::vec3 originalPos): Ghost(scene,"Pinky",originalPos)
{
	SDL_Rect srcRect{ 0,0,16,16 };
	m_MainGameObject->AddComponent<SpriteComponent>("Pinky.png", srcRect);
	m_MainGameObject->GetComponent<SpriteComponent>()->SetScale(2.f, 2.f);
}

void Pinky::InitializeFSM(dae::Scene* scene)
{
	scene;
}

Inky::Inky(dae::Scene* scene, const glm::vec3 originalPos) : Ghost(scene, "Inky",originalPos)
{
	SDL_Rect srcRect{ 0,0,16,16 };
	m_MainGameObject->AddComponent<SpriteComponent>("Inky.png", srcRect);
	m_MainGameObject->GetComponent<SpriteComponent>()->SetScale(2.f, 2.f);
}

void Inky::InitializeFSM(dae::Scene* scene)
{
	scene;
}

Clyde::Clyde(dae::Scene* scene, const glm::vec3 originalPos) : Ghost(scene, "Clyde",originalPos)
{
	SDL_Rect srcRect{ 0,0,16,16 };
	m_MainGameObject->AddComponent<SpriteComponent>("Clyde.png", srcRect);
	m_MainGameObject->GetComponent<SpriteComponent>()->SetScale(2.f, 2.f);
}

void Clyde::InitializeFSM(dae::Scene* scene)
{
	scene;
}

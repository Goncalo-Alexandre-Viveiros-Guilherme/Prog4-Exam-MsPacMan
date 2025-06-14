#include "MsPacMan.h"

#include "BoxColliderComponent.h"
#include "EventDispatcher.h"
#include "GameObject.h"
#include "Commands.h"
#include "ImageComponent.h"
#include "HealthComponent.h"
#include "MoveComponent.h"
#include "InputManager.h"
#include "PointsComponent.h"
#include "ResetPositionComponent.h"
#include "Scene.h"
#include "SpriteComponent.h"

MsPacMan::MsPacMan(const dae::Scene* scene, const glm::vec3 originalPos) : m_MainGameObject(nullptr)
{
	
	SDL_Rect srcRect { 0,0,16,16};
	m_MainGameObject = scene->GetGameObjectByName("MsPacMan");

	m_MainGameObject->SetLocalPosition(originalPos);

	m_MainGameObject->AddComponent<SpriteComponent>("MsPacMan.png", srcRect);
	m_MainGameObject->GetComponent<SpriteComponent>()->SetScale(2.f,2.f);
	m_MainGameObject->AddComponent<ResetPositionComponent>(originalPos);

	auto singleGridSize = glm::vec2{ 8 * 3, 8 * 3 };
	m_MainGameObject->AddComponent<BoxColliderComponent>(false, false, 8.f * 3.0f, 8.f * 3.f);
	m_MainGameObject->AddComponent<MoveComponent>(singleGridSize);
	m_MainGameObject->AddComponent<HealthComponent>(3.f);
	m_MainGameObject->AddComponent<PointsComponent>();
	

	auto moveComponent = m_MainGameObject->GetComponent<MoveComponent>();


	auto& inputManager = dae::InputManager::GetInstance();

	inputManager.AddInputMapping<MoveCommand>({ SDL_SCANCODE_W }, {}, KeyDown, 160.f, DesiredDirection::Up, moveComponent);
	inputManager.AddInputMapping<MoveCommand>({ SDL_SCANCODE_S }, {}, KeyDown, 160.f, DesiredDirection::Down, moveComponent);
	inputManager.AddInputMapping<MoveCommand>({ SDL_SCANCODE_A }, {}, KeyDown, 160.f, DesiredDirection::Left, moveComponent);
	inputManager.AddInputMapping<MoveCommand>({ SDL_SCANCODE_D }, {}, KeyDown, 160.f, DesiredDirection::Right, moveComponent);
}


dae::GameObject* MsPacMan::GetGameObject() const
{
	return m_MainGameObject;
}


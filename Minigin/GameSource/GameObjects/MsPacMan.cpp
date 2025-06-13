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
#include "Scene.h"
#include "SpriteComponent.h"

MsPacMan::MsPacMan(dae::Scene& scene) : m_MainGameObject(nullptr)
{
	auto obj = std::make_unique<dae::GameObject>("MsPacMan");
	SDL_Rect srcRect { 0,0,16,16};
	m_MainGameObject = obj.get();
	m_MainGameObject->AddComponent<SpriteComponent>("MsPacMan.png", srcRect);
	m_MainGameObject->GetComponent<SpriteComponent>()->SetScale(2.f,2.f);

	auto singleGridSize = glm::vec2{ 8 * 3, 8 * 3 };
	m_MainGameObject->AddComponent<BoxColliderComponent>(false, false, 8.f * 3.0f, 8.f * 3.f);
	m_MainGameObject->AddComponent<MoveComponent>(singleGridSize);
	m_MainGameObject->AddComponent<HealthComponent>(3.f);
	m_MainGameObject->AddComponent<PointsComponent>();
	scene.Add(std::move<>(obj));

	auto moveComponent = m_MainGameObject->GetComponent<MoveComponent>();


	auto& inputManager = dae::InputManager::GetInstance();

	inputManager.AddInputMapping<MoveCommand>({ SDL_SCANCODE_W }, {}, KeyDown, 160.f, DesiredDirection::Up, moveComponent);
	inputManager.AddInputMapping<MoveCommand>({ SDL_SCANCODE_S }, {}, KeyDown, 160.f, DesiredDirection::Down, moveComponent);
	inputManager.AddInputMapping<MoveCommand>({ SDL_SCANCODE_A }, {}, KeyDown, 160.f, DesiredDirection::Left, moveComponent);
	inputManager.AddInputMapping<MoveCommand>({ SDL_SCANCODE_D }, {}, KeyDown, 160.f, DesiredDirection::Right, moveComponent);

	inputManager.AddInputMapping<AddHealthCommand>({ SDL_SCANCODE_C }, {}, KeyPressed, -1.f,	m_MainGameObject->GetComponent<HealthComponent>());
	inputManager.AddInputMapping<AddPointsCommand>({ SDL_SCANCODE_Z }, {}, KeyPressed, 10.f,	m_MainGameObject->GetComponent<PointsComponent>());
	inputManager.AddInputMapping<AddPointsCommand>({ SDL_SCANCODE_X }, {}, KeyPressed, 100.f,	m_MainGameObject->GetComponent<PointsComponent>());
}


dae::GameObject* MsPacMan::GetGameObject() const
{
	return m_MainGameObject;
}

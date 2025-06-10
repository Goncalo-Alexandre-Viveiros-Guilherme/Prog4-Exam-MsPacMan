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
	m_MainGameObject = std::make_shared<dae::GameObject>("MsPacMan");
	SDL_Rect srcRect { 0,0,16,16};
	m_MainGameObject->AddComponent<SpriteComponent>("MsPacMan.png", srcRect);
	m_MainGameObject->AddComponent<MoveComponent>();
	m_MainGameObject->AddComponent<HealthComponent>(3.f);
	m_MainGameObject->AddComponent<BoxColliderComponent>(false, false, 16.f, 16.f, true);
	m_MainGameObject->AddComponent<PointsComponent>();
	scene.Add(m_MainGameObject);

	dae::InputManager::GetInstance().AddInputMapping<MoveCommand>({ SDL_SCANCODE_W }, {}, Down, 0.f, -250.0f,	m_MainGameObject->GetComponent<MoveComponent>());
	dae::InputManager::GetInstance().AddInputMapping<MoveCommand>({ SDL_SCANCODE_S }, {}, Down, 0.f, 250.0f,	m_MainGameObject->GetComponent<MoveComponent>());
	dae::InputManager::GetInstance().AddInputMapping<MoveCommand>({ SDL_SCANCODE_A }, {}, Down, -250.0f, 0.f,	m_MainGameObject->GetComponent<MoveComponent>());
	dae::InputManager::GetInstance().AddInputMapping<MoveCommand>({ SDL_SCANCODE_D }, {}, Down, 250.0f, 0.f,	m_MainGameObject->GetComponent<MoveComponent>());

	dae::InputManager::GetInstance().AddInputMapping<AddHealthCommand>({ SDL_SCANCODE_C }, {}, Pressed, -1.f,	m_MainGameObject->GetComponent<HealthComponent>());
	dae::InputManager::GetInstance().AddInputMapping<AddPointsCommand>({ SDL_SCANCODE_Z }, {}, Pressed, 10.f,	m_MainGameObject->GetComponent<PointsComponent>());
	dae::InputManager::GetInstance().AddInputMapping<AddPointsCommand>({ SDL_SCANCODE_X }, {}, Pressed, 100.f,	m_MainGameObject->GetComponent<PointsComponent>());
}


dae::GameObject* MsPacMan::GetGameObject() const
{
	return m_MainGameObject.get();
}

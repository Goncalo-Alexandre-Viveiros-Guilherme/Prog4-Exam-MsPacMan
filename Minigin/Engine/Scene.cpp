#include "Scene.h"
#include "GameObject.h"
#include "InputManager.h"
#include <algorithm>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(std::string name) : m_name(name) {}

Scene::~Scene()
{
	m_objects.clear();
}

std::string Scene::GetName() const
{
	return m_name;
}

void Scene::Add(std::unique_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(std::unique_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

GameObject* Scene::GetGameObjectByName(std::string name) const
{
	for (const auto& gameObj : m_objects)
	{
		if (gameObj->GetName() == name)
		{
			return gameObj.get();
		}	
	}

	throw std::runtime_error("No game object with that name found");
}

bool Scene::HasGameObjectByName(std::string name) const
{
	for (const auto& gameObj : m_objects)
	{
		if (gameObj->GetName() == name)
		{
			return true;
		}
	}
	return false;
}

std::vector<std::unique_ptr<GameObject>>& Scene::GetGameObjects()
{
	return m_objects;
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update() const
{
	for(auto& object : m_objects)
	{
		object->Update();
	}
}

void Scene::FixedUpdate() const
{
	for (auto& object : m_objects)
	{
		object->FixedUpdate();
	}
}

void Scene::DeleteObjects()
{
	std::erase_if(m_objects, [](const std::unique_ptr<GameObject>& o) { return o->GetIsMarkedForDestruction(); });
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}


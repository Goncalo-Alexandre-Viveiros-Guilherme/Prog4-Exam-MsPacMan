#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(std::string name) : m_name(name) {}

Scene::~Scene() = default;

std::string Scene::GetName() const
{
	return m_name;
}

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

std::shared_ptr<GameObject> Scene::GetGameObjectByName(std::string name) const
{
	for (const auto& gameObj : m_objects)
	{
		if (gameObj->GetName() == name)
		{
			return gameObj;
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

std::vector<std::shared_ptr<GameObject>>& Scene::GetGameObjects()
{
	return m_objects;
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update()
{
	for(auto& object : m_objects)
	{
		object->Update();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}


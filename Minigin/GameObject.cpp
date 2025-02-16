#include "GameObject.h"
#include "GameObject.h"

#include <string>
#include "GameObject.h"

#include "ResourceManager.h"
#include "Transform.h"


std::string dae::GameObject::GetName()
{
	return m_Name;	
}

void dae::GameObject::DeleteComponent(Component& componentToDelete)
{
	for (Component* component : m_Components)
	{
		if (component == &componentToDelete)
		{
			delete component;
			m_Components.erase(std::remove(m_Components.begin(), m_Components.end(), component), m_Components.end());
			break;
		}
	}
}

dae::GameObject::GameObject(std::string name) : m_IsEnabled(true), m_Name(name)
{
}

dae::GameObject::~GameObject()
{
	for (Component* component : m_Components)
	{
		delete component;
	}

	m_Components.clear();
};

void dae::GameObject::Update() 
{
	for (const auto& component : m_Components)
	{
		component->Update();
	}
}

void dae::GameObject::Render() const
{
	for (const auto& component : m_Components)
	{
		component->Render();
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

const glm::vec3& dae::GameObject::GetPosition() const
{
	return m_Transform.GetPosition();
}

void dae::GameObject::SetToDestroy()
{
	m_IsMarkedForDestruction = true;
}

bool dae::GameObject::GetIsMarkedForDestruction() const
{
	return m_IsMarkedForDestruction;
}

std::vector<Component*> dae::GameObject::GetAllComponents()
{
	return m_Components;
}

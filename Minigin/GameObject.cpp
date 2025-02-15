#include <string>
#include "GameObject.h"

#include "RenderComponent.h"
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

dae::GameObject::GameObject(std::string name) : m_Name(name)	
{
	AddComponent<Transform>();
}

dae::GameObject::~GameObject()
{
	for (Component* component : m_Components)
	{
		delete component;
	}

	m_Components.clear();
};

void dae::GameObject::Update(){}

void dae::GameObject::Render() const
{
	if (HasComponent<RenderComponent>())
		if (GetComponent<RenderComponent>().GetIsEnabled() == true)
		{
			const auto& pos = GetComponent<Transform>().GetPosition();
			GetComponent<RenderComponent>().Render(pos.x, pos.y);
		}
}

void dae::GameObject::SetPosition(float x, float y) const
{
	GetComponent<Transform>().SetPosition(x, y, 0.0f);
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

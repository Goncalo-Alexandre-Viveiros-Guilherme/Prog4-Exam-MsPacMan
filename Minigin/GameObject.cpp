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

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
{
	if (IsChild(parent) || parent == this || m_Parent == parent)
		return;
	if (parent == nullptr)
		SetLocalPosition(GetWorldPosition());
	else
	{
		if (keepWorldPosition)
			SetLocalPosition(GetWorldPosition() - parent->GetWorldPosition());
		SetPositionDirty();
	}
	if (m_Parent) m_Parent->RemoveChild(this);
	m_Parent = parent;
	if (m_Parent) m_Parent->AddChild(this);
}

dae::GameObject::GameObject(std::string name) : m_IsEnabled(true), m_Parent(nullptr), m_Name(name)
{
}

dae::GameObject::~GameObject()
{
	for (const Component* component : m_Components)
	{
		delete component;
	}

	m_Components.clear();
}

void dae::GameObject::AddChild(GameObject* child)
{
	if (child == nullptr)
		return;
	if (child->m_Parent == this)
		return;
	if (child->m_Parent)
		child->m_Parent->RemoveChild(child);
	child->m_Parent = this;
	m_Children.push_back(child);
}

void dae::GameObject::RemoveChild(GameObject* child)
{
	if (child == nullptr)
		return;
	if (child->m_Parent != this)
		return;
	child->m_Parent = nullptr;
	m_Children.erase(std::ranges::remove(m_Children, child).begin(), m_Children.end());
}

bool dae::GameObject::IsChild(GameObject* child) const
{
	return std::ranges::find(m_Children, child) != m_Children.end();
}

void dae::GameObject::SetPositionDirty()
{
	m_IsPositionDirty = true;
};

void dae::GameObject::Update() const
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

void dae::GameObject::SetLocalPosition(float x, float y)
{
	m_Transform.SetLocalPosition(x, y, 0.0f);
	SetPositionDirty();
}

void dae::GameObject::SetLocalPosition(const glm::vec3& pos)
{
	m_Transform.SetLocalPosition(pos);
	SetPositionDirty();
}

const glm::vec3& dae::GameObject::GetLocalPosition() const
{
	return m_Transform.GetLocalPosition();
}

void dae::GameObject::UpdateWorldPosition() 
{
	if (m_IsPositionDirty)
	{
		if (m_Parent == nullptr)
			m_Transform.SetWorldPosition(m_Transform.GetLocalPosition());
		else
			m_Transform.SetWorldPosition(m_Parent->GetWorldPosition() + m_Transform.GetLocalPosition());
	}
	m_IsPositionDirty = false;

}

const glm::vec3& dae::GameObject::GetWorldPosition()
{
	if (m_IsPositionDirty)
		UpdateWorldPosition();
	return m_Transform.GetWorldPosition();
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

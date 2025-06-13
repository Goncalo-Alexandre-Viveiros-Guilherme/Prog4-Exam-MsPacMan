#include "GameObject.h"
#include <iostream>
#include <string>
#include "ResourceManager.h"
#include "Transform.h"

std::string dae::GameObject::GetName()
{
    return m_Name;
}

void dae::GameObject::DeleteComponent(const Component& componentToDelete)
{
    auto it = std::remove_if(m_Components.begin(), m_Components.end(),
        [&](const auto& component) {
            return component.get() == &componentToDelete;
        });

    if (it != m_Components.end()) {
        m_Components.erase(it);
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

bool dae::GameObject::HasParent() const
{
    return m_Parent != nullptr;
}

std::vector<dae::GameObject*>& dae::GameObject::GetGameObjectChildren()
{
    return m_Children;
}

dae::GameObject::GameObject(const std::string& name) :
    m_IsEnabled(true),
    m_Parent(nullptr),
    m_Name(name)
{
    std::cerr << "my name is: " << m_Name;
}

dae::GameObject::~GameObject()
{
    if (m_Parent) {
        m_Parent->RemoveChild(this);
    }

    for (auto* child : m_Children) {
        child->m_Parent = nullptr;
    }
}

void dae::GameObject::AddChild(GameObject* child)
{
    if (!IsChild(child)) {
        m_Children.push_back(child);
    }
}

void dae::GameObject::RemoveChild(GameObject* child)
{
    m_Children.erase(std::ranges::remove(m_Children, child).begin(), m_Children.end());
}

bool dae::GameObject::IsChild(GameObject* child) const
{
    return std::ranges::find(m_Children, child) != m_Children.end();
}

void dae::GameObject::SetPositionDirty()
{
    m_IsPositionDirty = true;
    for (const auto& child : m_Children) {
        child->SetPositionDirty();
    }
}

void dae::GameObject::Update()
{
    for (auto& component : m_Components) {
        component->Update();
    }

    std::erase_if(m_Components,
        [](const auto& component) {
            return component->GetIsMarkedForDestruction();
        });
}

void dae::GameObject::FixedUpdate() const
{
    for (const auto& component : m_Components) {
        component->FixedUpdate();
    }
}

void dae::GameObject::Render() const
{
    for (const auto& component : m_Components) {
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
    if (m_IsPositionDirty) {
        if (m_Parent == nullptr) {
            m_Transform.SetWorldPosition(m_Transform.GetLocalPosition());
        }
        else {
            m_Transform.SetWorldPosition(
                m_Parent->GetWorldPosition() + m_Transform.GetLocalPosition());
        }
        m_IsPositionDirty = false;
    }
}

const glm::vec3& dae::GameObject::GetWorldPosition()
{
    if (m_IsPositionDirty) {
        UpdateWorldPosition();
    }
    return m_Transform.GetWorldPosition();
}

void dae::GameObject::SetToDestroy()
{
    m_IsMarkedForDestruction = true;
    for (auto& child : m_Children) {
        child->SetToDestroy();
    }
}

bool dae::GameObject::GetIsMarkedForDestruction() const
{
    return m_IsMarkedForDestruction;
}

std::vector<Component*> dae::GameObject::GetAllComponents()
{
    std::vector<Component*> rawComponents;
    rawComponents.reserve(m_Components.size());
    for (auto& component : m_Components) {
        rawComponents.push_back(component.get());
    }
    return rawComponents;
}
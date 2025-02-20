#include "Component.h"

#include <stdexcept>


Component::Component(const dae::GameObject& parent) 
    : m_Parent(&parent), m_IsEnabled(true)
{
}

void Component::Update()
{
}

void Component::Render()
{
}

const dae::GameObject* Component::GetParent() const
{
	return m_Parent;
}

void Component::SetToDestroy()
{
	m_IsMarkedForDestruction = true;
}

void Component::SetIsEnabled(bool value)
{
	m_IsEnabled = value;
}

bool Component::GetIsEnabled() const
{
	return m_IsEnabled;
}

bool Component::GetIsMarkedForDestruction() const
{
	return m_IsMarkedForDestruction;
}

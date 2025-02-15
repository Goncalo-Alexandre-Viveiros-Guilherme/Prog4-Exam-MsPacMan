#include "Component.h"


Component::Component(const dae::GameObject* parent) // Ensure this matches the argument type in AddComponent
    : m_Parent(parent), m_IsEnabled(true)
{
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

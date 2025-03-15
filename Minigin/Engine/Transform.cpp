#include "Transform.h"

dae::Transform::Transform(): m_LocalPosition(0, 0, 0), m_WorldPosition(0,0,0)
{
}

void dae::Transform::SetLocalPosition(const float x, const float y, const float z)
{
	m_LocalPosition.x = x;
	m_LocalPosition.y = y;
	m_LocalPosition.z = z;
}

void dae::Transform::SetLocalPosition(const glm::vec3& pos)
{
	m_LocalPosition = pos;
}

void dae::Transform::SetWorldPosition(float x, float y, float z)
{
	m_WorldPosition.x = x;
	m_WorldPosition.y = y;
	m_WorldPosition.z = z;
}

void dae::Transform::SetWorldPosition(const glm::vec3& pos)
{
	m_WorldPosition = pos;
}

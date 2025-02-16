#include "Transform.h"

dae::Transform::Transform(): m_position(0,0,0)
{
}

void dae::Transform::SetPosition(const float x, const float y, const float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

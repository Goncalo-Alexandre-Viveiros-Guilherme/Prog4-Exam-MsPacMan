#pragma once

#include "Component.h"
#include "vec3.hpp"

class RotatorComponent : public Component
{
public:
	RotatorComponent(dae::GameObject& parent,float angle,float radius);

	void Update() override;
	void SetAngleSpeed(float angleSpeed);
	void SetRadius(float radius);

private:
	bool m_IsStaticPoint{ };
	glm::vec3 m_CenterPos{};
	float m_AngleSpeed;
	float m_Angle;
	float m_Radius;
};

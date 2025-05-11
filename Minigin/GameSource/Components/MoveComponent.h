#pragma once
#include "Component.h"

class MoveComponent : public Component
{
public:
	MoveComponent(dae::GameObject& parent);
	void Update() override;
	void SetSpeed(float speedX, float speedY);

private:
	float m_SpeedX;
	float m_SpeedY;
};

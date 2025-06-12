#pragma once
#include "Component.h"
#include "vec2.hpp"
#include "vec3.hpp"

enum DesiredDirection
{
	Up,
	Down,	
	Left,
	Right,
	None
};

class MoveComponent : public Component
{
public:
	MoveComponent(dae::GameObject& parent, glm::vec2 gridSize);
	void Update() override;
	bool WouldCollide(const glm::vec3& position) const;
	bool IsNearGridIntersection(const glm::vec3& pos) const;
	bool CanMove(DesiredDirection direction);
	bool IsCollidingAABB(float ax, float ay, float bx, float by, float bw, float bh) const;
	glm::vec2 GetDirectionOffset(DesiredDirection dir) const;
	void SetDesiredDirection(DesiredDirection desiredDirection);
	void SetSpeed(float speed);

private:
	float m_Speed;
	glm::vec2 m_GridSize;
	DesiredDirection m_DesiredDirection;
	DesiredDirection m_CurrentDirection;
};

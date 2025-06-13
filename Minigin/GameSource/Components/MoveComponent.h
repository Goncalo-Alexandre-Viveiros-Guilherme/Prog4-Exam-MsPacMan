#pragma once
#include "Achievements.h"
#include "Achievements.h"
#include "Achievements.h"
#include "Achievements.h"
#include "Component.h"
#include "vec2.hpp"
#include "vec3.hpp"

class CollisionComponent;

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
	MoveComponent(dae::GameObject* parent, glm::vec2 gridSize);
	void Update() override;
	bool CanMove(DesiredDirection direction);
	glm::vec2 GetDirectionOffset(DesiredDirection dir) const;
	bool IsNearGridIntersection(const glm::vec3& pos) const;
	bool IsAtGridCenter(const glm::vec3& pos) const;
	void SetDesiredDirection(DesiredDirection desiredDirection);
	void SetSpeed(float speed);

	DesiredDirection GetCurrentDirection() const {return m_CurrentDirection;}
	glm::vec2 GetGridSize() { return m_GridSize; }

private:
	float m_Speed;
	glm::vec2 m_GridSize;
	DesiredDirection m_DesiredDirection;
	DesiredDirection m_CurrentDirection;
	CollisionComponent* m_CollisionComponent;
};

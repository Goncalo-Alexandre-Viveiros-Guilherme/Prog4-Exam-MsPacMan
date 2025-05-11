#include "MoveComponent.h"

#include "EngineTime.h"
#include "EventDispatcher.h"
#include "Events.h"
#include "GameObject.h"

MoveComponent::MoveComponent(dae::GameObject& parent): Component(parent), m_SpeedX(0), m_SpeedY(0)
{
}

void MoveComponent::Update()
{
	glm::vec3 pos = GetParent()->GetWorldPosition();
	GetParent()->SetLocalPosition(pos.x + (m_SpeedX * Time::GetInstance().GetDeltaTime()), pos.y + (m_SpeedY * Time::GetInstance().GetDeltaTime()));

	if (m_SpeedX == 0 || m_SpeedY == 0)
	{
		FSM::NewState event(FSM::States::MovingState);
		EventDispatcher::GetInstance().Dispatch(event, GetParent());
	}
}

void MoveComponent::SetSpeed(float speedX, float speedY)
{
	m_SpeedX = speedX;
	m_SpeedY = speedY;
}

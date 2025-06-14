#ifndef RESETPOSITIONCOMPONENT_H
#define RESETPOSITIONCOMPONENT_H
#include "Component.h"
#include "FSMComponent.h"
#include "GhostStates.h"
#include "vec3.hpp"
#include"HealthComponent.h"

class ResetPositionComponent : public Component
{
public:
	ResetPositionComponent(dae::GameObject* parent, const glm::vec3 pos,bool isGhost = false):
	Component(parent),
	m_PosToSave(pos),
	m_IsGhost(isGhost)
	{
		EventDispatcher::GetInstance().AddListener<ResetEntityPosEvent>
			(nullptr, [this](const ResetEntityPosEvent& event)
				{
					SetParentObjToSavedPos(event.m_DispatchingObj);
				}
			);
	}

	void SetParentObjToSavedPos(const dae::GameObject* dispatchingObject) const
	{
		bool isWeak = dispatchingObject->GetComponent<FSMComponent>()->GetCurrentState()->is<FSM::BlinkyFrightenedState>();
		if (m_IsGhost)
		{
			if (isWeak)
			{
				AddPointsEvent event(500);
				EventDispatcher::GetInstance().Dispatch(event, GetParent());

				if (dispatchingObject == GetParent())
				{
					GetParent()->GetComponent<MoveComponent>()->SetDesiredDirection(None);
					GetParent()->SetLocalPosition(m_PosToSave);
				}
			}
			else
			{
				GetParent()->GetComponent<MoveComponent>()->SetDesiredDirection(None);
				GetParent()->SetLocalPosition(m_PosToSave);
				return;

			}
		}
		else
		{
			if (!isWeak)
			{
				GetParent()->GetComponent<MoveComponent>()->SetDesiredDirection(None);
				GetParent()->GetComponent<HealthComponent>()->AddToHealth(-1);
				GetParent()->SetLocalPosition(m_PosToSave);
			}

		}
		
	}

	~ResetPositionComponent() = default;
private:
	glm::vec3 m_PosToSave;
	bool m_IsGhost{false};
	bool m_IsWeak{ false };
};
#endif // RESETPOSITIONCOMPONENT_H

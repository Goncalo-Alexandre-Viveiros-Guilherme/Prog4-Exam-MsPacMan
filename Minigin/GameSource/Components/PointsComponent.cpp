#include "PointsComponent.h"
#include "EventDispatcher.h"
#include "Events.h"

PointsComponent::PointsComponent(dae::GameObject& parent) : Component(parent), m_CurrentPoints(0)
{
	EventDispatcher::GetInstance().AddListener<AddPointsEvent>
		(nullptr, [this](const AddPointsEvent& event)
			{
				AddToPoints(event.m_AmountToAdd);
			}
		);
}

void PointsComponent::AddToPoints(const float value)
{
	m_CurrentPoints += value;
	PointsChangedEvent event(m_CurrentPoints);
	EventDispatcher::GetInstance().Dispatch(event, GetParent());
}

float PointsComponent::GetPoints() const
{
	return m_CurrentPoints;
}
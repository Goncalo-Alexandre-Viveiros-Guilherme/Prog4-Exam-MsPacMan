#include "PointDisplayComponent.h"

#include "GameObject.h"
#include "TextComponent.h"
#include "Events.h"
#include "EventDispatcher.h"

PointDisplayComponent::PointDisplayComponent(dae::GameObject& parent, PointsComponent* healthComponent) :
	Component(parent), m_AssociatedPointsComp(healthComponent)
{
	if (!parent.HasComponent<TextComponent>())
		throw std::runtime_error("Error: " + parent.GetName() + " does not have a Text Component");
	m_TextComponent = parent.GetComponent<TextComponent>();

	EventDispatcher::GetInstance().AddListener<PointsChangedEvent>
		([this](const PointsChangedEvent& event)
			{
				if (event.m_PointsComponent == m_AssociatedPointsComp)
				{
					UpdateDisplay(event.m_Points);
				}
			}
		);
}

void PointDisplayComponent::UpdateDisplay(float health) const
{
	m_TextComponent->SetText("Score: " + std::to_string(static_cast<int>(health)));
}
#include "PointDisplayComponent.h"

#include "GameObject.h"
#include "TextComponent.h"
#include "Events.h"
#include "EventDispatcher.h"

PointDisplayComponent::PointDisplayComponent(dae::GameObject* parent, dae::GameObject* associatedGameObj) :
	Component(parent)
{
	if (!parent->HasComponent<TextComponent>())
		throw std::runtime_error("Error: " + parent->GetName() + " does not have a Text Component");
	m_TextComponent = parent->GetComponent<TextComponent>();

	EventDispatcher::GetInstance().AddListener<PointsChangedEvent>
		(associatedGameObj, [this](const PointsChangedEvent& event)
			{
				UpdateDisplay(event.m_Points);
			}
		);
}

void PointDisplayComponent::UpdateDisplay(float health) const
{
	m_TextComponent->SetText("Score: " + std::to_string(static_cast<int>(health)));
}
#include "HealthDisplayComponent.h"

#include "GameObject.h"
#include "TextComponent.h"
#include "Events.h"
#include "EventDispatcher.h"

HealthDisplayComponent::HealthDisplayComponent(dae::GameObject& parent, dae::GameObject* associatedGameObj) :
	Component(parent)
{
	if (!parent.HasComponent<TextComponent>())
		throw std::runtime_error("Error: " + parent.GetName() + " does not have a Text Component");
	m_TextComponent = parent.GetComponent<TextComponent>();

	EventDispatcher::GetInstance().AddListener<HealthChangedEvent>
		(associatedGameObj, [this](const HealthChangedEvent& event)
			{
				UpdateDisplay(event.m_NewHealth);
			}
		);
}

void HealthDisplayComponent::UpdateDisplay(float health) const
{
	m_TextComponent->SetText("# lives: " + std::to_string(static_cast<int>(health)));
}
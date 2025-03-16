#include "HealthDisplayComponent.h"

#include "GameObject.h"
#include "HealthComponent.h"
#include "TextComponent.h"
#include "Events.h"
#include "EventDispatcher.h"

HealthDisplayComponent::HealthDisplayComponent(dae::GameObject& parent, HealthComponent* healthComponent):
Component(parent), m_AssociatedHealthComp(healthComponent)
{
	if (!parent.HasComponent<TextComponent>())
		throw std::runtime_error("Error: " + parent.GetName() + " does not have a Text Component");
	m_TextComponent = parent.GetComponent<TextComponent>();

	EventDispatcher::GetInstance().AddListener<HealthChangedEvent>
	([this](const HealthChangedEvent& event) 
		{
			if (event.m_HealthComponent == m_AssociatedHealthComp)
			{
				UpdateDisplay(event.m_NewHealth);
			}
		}
	);
}

void HealthDisplayComponent::UpdateDisplay(float health) const
{
	m_TextComponent->SetText("# lives: " + std::to_string(static_cast<int>(health)));
}

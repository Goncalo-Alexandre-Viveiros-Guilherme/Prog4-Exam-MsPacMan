#include "HealthDisplayComponent.h"

#include "GameObject.h"
#include "HealthComponent.h"
#include "TextComponent.h"
#include "Events.h"
#include "EventDispatcher.h"

HealthDisplayComponent::HealthDisplayComponent(dae::GameObject& parent): Component(parent)
{
	if (!parent.HasComponent<TextComponent>())
		throw std::runtime_error("Error: " + parent.GetName() + " does not have a Text Component");
	m_TextComponent = &parent.GetComponent<TextComponent>();

	if (!parent.HasComponent<HealthComponent>())
		throw std::runtime_error("Error: " + parent.GetName() + " does not have a Health Component");

	EventDispatcher::GetInstance().AddListener<HealthChangedEvent>(
		[this](const HealthChangedEvent& event) 
		{
			UpdateDisplay(event.newHealth);
		}
	);
}

void HealthDisplayComponent::UpdateDisplay(float health) const
{
	m_TextComponent->SetText("# lives: " + std::to_string(health));
}

void HealthDisplayComponent::OnHealthChanged(float healthAmount) const
{
	m_TextComponent->SetText("# lives: " + std::to_string(healthAmount));
}

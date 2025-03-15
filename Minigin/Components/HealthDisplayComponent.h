#pragma once
#include "Component.h"


class TextComponent;

class HealthDisplayComponent : public Component
{
public:
	HealthDisplayComponent(dae::GameObject& parent);
	void UpdateDisplay(float health) const;

	void OnHealthChanged(float healthAmount) const;

private:
	TextComponent* m_TextComponent;
};

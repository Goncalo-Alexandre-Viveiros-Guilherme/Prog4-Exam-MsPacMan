#pragma once
#include "Component.h"


class HealthComponent;
class TextComponent;

class HealthDisplayComponent : public Component
{
public:
	HealthDisplayComponent(dae::GameObject& parent, HealthComponent* healthComponent);
	void UpdateDisplay(float health) const;


private:
	TextComponent* m_TextComponent;
	HealthComponent* m_AssociatedHealthComp;
};

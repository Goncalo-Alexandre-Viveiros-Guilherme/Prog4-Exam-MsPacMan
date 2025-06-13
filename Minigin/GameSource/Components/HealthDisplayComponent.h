#pragma once
#include "Component.h"


class HealthComponent;
class TextComponent;

class HealthDisplayComponent : public Component
{
public:
	HealthDisplayComponent(dae::GameObject* parent, dae::GameObject* associatedGameObj);
	void UpdateDisplay(float health) const;


private:
	TextComponent* m_TextComponent;
};

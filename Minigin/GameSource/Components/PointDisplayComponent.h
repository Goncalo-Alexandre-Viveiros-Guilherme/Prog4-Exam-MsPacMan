#pragma once
#include "Component.h"


class PointsComponent;
class TextComponent;

class PointDisplayComponent : public Component
{
public:
	PointDisplayComponent(dae::GameObject& parent, dae::GameObject* associatedGameObj);
	void UpdateDisplay(float health) const;

private:
	TextComponent* m_TextComponent;
};
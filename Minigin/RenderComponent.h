#pragma once 

#include "Component.h"

class RenderComponent : public Component
{
public:
	RenderComponent(const dae::GameObject* parent);

	void Render(float posx,float poxy) const;
};
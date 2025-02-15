#include "RenderComponent.h"

#include "GameObject.h"
#include "ImageComponent.h"
#include "Renderer.h"
#include "TextComponent.h"

RenderComponent::RenderComponent(const dae::GameObject* parent) :Component(parent)
{
}

void RenderComponent::Render(float posx, float poxy) const
{
	if (m_Parent->HasComponent<TextComponent>())
	{
		const auto textTex = m_Parent->GetComponent<TextComponent>().GetTex();
		if (textTex != nullptr)
		{
			dae::Renderer::GetInstance().RenderTexture(*textTex, posx, poxy);
		}
		
	}

	if (m_Parent->HasComponent<ImageComponent>())
	{
		const auto tex = m_Parent->GetComponent<ImageComponent>().GetTex();
		if (tex != nullptr)
		{
			dae::Renderer::GetInstance().RenderTexture(*tex, posx, poxy);
		}
		
	}
}

#include "SpriteComponent.h"

#include <algorithm>
#include <memory>

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "SDL_rect.h"
#include "Texture2D.h"


SpriteComponent::SpriteComponent(dae::GameObject& parent, const std::string& filename, SDL_Rect srcRect):
Component(parent),
 m_SrcRect(srcRect)
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}

SpriteComponent::SpriteComponent(dae::GameObject& parent, const std::string& filename, SDL_Rect srcRect, int dstWidth,int dstHeight): 
	Component(parent),
	m_SrcRect(srcRect),
	m_DstWidth(dstWidth),
	m_DstHeight(dstHeight)
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}

void SpriteComponent::SetScale(float scaleX, float scaleY)
{
	m_SpriteScaleX = scaleX;
	m_SpriteScaleY = scaleY;
}

void SpriteComponent::Render()
{
	if (!m_Texture) return;

	if (m_DstWidth > 0 || m_DstHeight > 0)
	{
		SDL_Rect dst{};
		dst.x = static_cast<int>(GetParent()->GetWorldPosition().x);
		dst.y = static_cast<int>(GetParent()->GetWorldPosition().y);
		dst.w = m_DstWidth;
		dst.h = m_DstHeight;
		dae::Renderer::GetInstance().RenderTexture(*m_Texture, m_SrcRect, dst,m_SpriteScaleX,m_SpriteScaleY);
	}
	else
	{
		dae::Renderer::GetInstance().RenderTexture(*m_Texture, m_SrcRect, GetParent()->GetWorldPosition(), m_SpriteScaleX, m_SpriteScaleY);
	}

}


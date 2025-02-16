#include "ImageComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"

ImageComponent::ImageComponent(const dae::GameObject* parent): Component(parent)
{
}

void ImageComponent::Render()
{
	dae::Renderer::GetInstance().RenderTexture(*m_texture, m_Parent->GetPosition().x, m_Parent->GetPosition().y);
}

void ImageComponent::SetTexture(const std::string& filename)
{
	m_texture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}

std::shared_ptr<dae::Texture2D> ImageComponent::GetTex()
{
	return m_texture;
}

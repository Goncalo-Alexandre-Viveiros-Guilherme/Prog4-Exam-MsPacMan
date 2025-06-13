#include "ImageComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"

ImageComponent::ImageComponent(dae::GameObject* parent): Component(parent)
{
}

ImageComponent::ImageComponent(dae::GameObject* parent, const std::string& filename): Component(parent)
{
	m_texture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}

void ImageComponent::Render()
{
	dae::Renderer::GetInstance().RenderTexture(*m_texture, GetParent()->GetWorldPosition().x, GetParent()->GetWorldPosition().y);
}

void ImageComponent::SetTexture(const std::string& filename)
{
	m_texture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}

std::shared_ptr<dae::Texture2D> ImageComponent::GetTex()
{
	return m_texture;
}

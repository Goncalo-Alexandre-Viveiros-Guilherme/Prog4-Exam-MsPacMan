#include "ImageComponent.h"

#include "ResourceManager.h"

ImageComponent::ImageComponent(const dae::GameObject* parent): Component(parent)
{
}

void ImageComponent::SetTexture(const std::string& filename)
{
	m_texture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}

std::shared_ptr<dae::Texture2D> ImageComponent::GetTex()
{
	return m_texture;
}

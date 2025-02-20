#pragma once
#include <memory>
#include <string>

#include "Component.h"

namespace dae
{
	class Texture2D;
}

class ImageComponent : public Component
{
public:
	ImageComponent(const dae::GameObject& parent);
	void Render() override;
	void SetTexture(const std::string& filename);
	std::shared_ptr<dae::Texture2D> GetTex();


private:
	std::shared_ptr<dae::Texture2D> m_texture{};
	
};

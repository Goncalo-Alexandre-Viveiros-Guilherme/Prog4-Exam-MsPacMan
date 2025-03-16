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
	ImageComponent(dae::GameObject& parent);
	ImageComponent(dae::GameObject& parent, const std::string& filename);
	void Render() override;
	void SetTexture(const std::string& filename);
	std::shared_ptr<dae::Texture2D> GetTex();


private:
	std::shared_ptr<dae::Texture2D> m_texture{};
	
};

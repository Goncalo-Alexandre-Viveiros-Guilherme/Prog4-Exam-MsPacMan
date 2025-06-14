#pragma once
#include <memory>
#include <string>
#include "Component.h"
#include "SDL_pixels.h"
#include "vec2.hpp"

namespace dae
{
	class Texture2D;
	class Font;
}

class TextComponent : public Component
{
public:
	explicit TextComponent(dae::GameObject* parent, const std::string& text, std::shared_ptr<dae::Font> font);

	explicit TextComponent(dae::GameObject* parent, const std::string& text, std::shared_ptr<dae::Font> font, glm::vec2 textOffset);

	void Update();
	void Render() override;
	void SetText(const std::string& text);
	void SetColor(const SDL_Color& color);
	std::shared_ptr<dae::Texture2D> GetTex();



private:
	SDL_Color m_Color{ 255, 255, 255, 255 };
	std::string m_text {};
	std::shared_ptr<dae::Font> m_font{ nullptr };
	std::shared_ptr<dae::Texture2D> m_textTexture {nullptr};
	glm::vec2 m_TextOffset {};
};

#pragma once
#include <memory>
#include <string>
#include "Component.h"

namespace dae
{
	class Texture2D;
	class Font;
}

class TextComponent : public Component
{
public:
	explicit TextComponent(const dae::GameObject* parent, const std::string& text, std::shared_ptr<dae::Font> font);

	void Update();
	void Render() override;
	void SetText(const std::string& text);
	std::shared_ptr<dae::Texture2D> GetTex();

private:
	std::string m_text;
	std::shared_ptr<dae::Font> m_font;
	std::shared_ptr<dae::Texture2D> m_textTexture;
};

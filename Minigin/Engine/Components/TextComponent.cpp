#include "TextComponent.h"

#include <stdexcept>

#include "Font.h"
#include "GameObject.h"
#include "Renderer.h"
#include "SDL_pixels.h"
#include "SDL_ttf.h"
#include "Texture2D.h"


TextComponent::TextComponent(dae::GameObject* parent, const std::string& text, std::shared_ptr<dae::Font> font)
	: Component(parent), m_text(text), m_font(font)
{
	
}

TextComponent::TextComponent(dae::GameObject* parent, const std::string& text, std::shared_ptr<dae::Font> font,
	glm::vec2 textOffset): Component(parent), m_text(text), m_font(font), m_TextOffset(textOffset)
{
}

void TextComponent::Update()
{
	const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), m_Color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);
	m_textTexture = std::make_shared<dae::Texture2D>(texture);
}

void TextComponent::Render()
{
	dae::Renderer::GetInstance().RenderTexture(*m_textTexture, GetParent()->GetWorldPosition().x + m_TextOffset.x, GetParent()->GetWorldPosition().y + m_TextOffset.y);
}

void TextComponent::SetText(const std::string& text)
{
	m_text = text;
}

void TextComponent::SetColor(const SDL_Color& color)
{
	m_Color = color;
}
std::shared_ptr<dae::Texture2D> TextComponent::GetTex()
{
	return m_textTexture;
}

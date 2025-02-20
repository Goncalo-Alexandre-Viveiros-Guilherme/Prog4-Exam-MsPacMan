#include "TextComponent.h"

#include <stdexcept>

#include "Font.h"
#include "GameObject.h"
#include "Renderer.h"
#include "SDL_pixels.h"
#include "SDL_ttf.h"
#include "Texture2D.h"


TextComponent::TextComponent(const dae::GameObject& parent, const std::string& text, std::shared_ptr<dae::Font> font)
	: Component(parent), m_text(text), m_font(font)
{
	
}

void TextComponent::Update()
{
	const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
	const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), color);
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
	dae::Renderer::GetInstance().RenderTexture(*m_textTexture, GetParent()->GetLocalPosition().x, GetParent()->GetLocalPosition().y);
}

void TextComponent::SetText(const std::string& text)
{
	m_text = text;
}

std::shared_ptr<dae::Texture2D> TextComponent::GetTex()
{
	return m_textTexture;
}

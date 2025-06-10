#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H
#include <memory>
#include <string>

#include "Component.h"
#include "SDL_rect.h"

namespace dae
{
	class Texture2D;
}

class SpriteComponent : public Component
{
public:
	SpriteComponent(dae::GameObject& parent, const std::string& filename, SDL_Rect srcRect);

	SpriteComponent(dae::GameObject& parent, const std::string& filename, SDL_Rect srcRect, int dstWidth,int dstHeight);

	void SetScale(float scaleX,float scaleY);

	void Render() override;

private:
	std::shared_ptr<dae::Texture2D> m_Texture;
	SDL_Rect m_SrcRect;
	int m_DstWidth = 0;
	int m_DstHeight = 0;
	int m_SpriteScaleX = 1;
	int m_SpriteScaleY = 1;
};
#endif // SPRITECOMPONENT_H

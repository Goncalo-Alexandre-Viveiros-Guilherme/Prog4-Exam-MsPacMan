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
	SpriteComponent(dae::GameObject* parent, const std::string& filename, SDL_Rect srcRect, float rotation = 0);

	SpriteComponent(dae::GameObject* parent, const std::string& filename, SDL_Rect srcRect, int dstWidth,int dstHeight, float rotation = 0);

	void SetScale(float scaleX,float scaleY);

	void Render() override;

private:
	std::shared_ptr<dae::Texture2D> m_Texture;
	SDL_Rect m_SrcRect;
	int m_DstWidth = 0;
	int m_DstHeight = 0;
	float m_SpriteScaleX = 1;
	float m_SpriteScaleY = 1;
	float m_SpriteRot = 0;
};
#endif // SPRITECOMPONENT_H

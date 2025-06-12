#ifndef BOXCOLLIDERCOMPONENT_H
#define BOXCOLLIDERCOMPONENT_H

#include "CollisionComponent.h"

class Event;

class BoxColliderComponent : public CollisionComponent
{
public:
	BoxColliderComponent(dae::GameObject& parent,bool isStatic,bool blockOnCollision,float width, float height, bool debugRender = false);

	BoxColliderComponent(dae::GameObject& parent,bool isStatic,bool blockOnCollision,glm::vec2 size,glm::vec2 offset, bool debugRender = false);

	~BoxColliderComponent();

	void FixedUpdate() override;

	void Render() override;

	bool GetIsBlocking() const { return m_BlockOnCollision; }

	glm::vec2 GetLocalColliderPosition() const {return m_Location;}
	bool IsCollidingInDirection(const glm::vec2 direction, float checkDistance) const;

private:
	bool IsCollidingAABB(float ax, float ay,float bx, float by, float bw, float bh) const;

	bool m_DebugRenderingActive = false;
};
#endif // BOXCOLLIDERCOMPONENT_H

#pragma once
#include "Component.h"
#include "vec2.hpp"
#include "vec3.hpp"

class Event;

class BoxColliderComponent : public Component
{
public:
	BoxColliderComponent(dae::GameObject& parent,bool isStatic,bool blockOnCollision,float width, float height, bool debugRender = false);

	void FixedUpdate() override;

	void AddOnEnterEvent(const Event& event) const;
	void AddWhileInEvent(const Event& event) const;
	void AddWhileOutEvent(const Event& event) const;
	void AddOnExitEvent(const Event& event) const;

	void Render() override;

	bool GetIsBlocking() const { return m_BlockOnCollision; }

private:
	bool IsCollidingAABB(float ax, float ay,float bx, float by, float bw, float bh) const;


	bool m_IsStatic			= false;
	bool m_BlockOnCollision = true;
	bool m_DebugRenderingActive = false;
	glm::vec2 m_Size		{};
	glm::vec3 m_LastSafePos {};
};

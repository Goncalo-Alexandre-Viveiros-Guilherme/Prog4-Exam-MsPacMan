#include "BoxColliderComponent.h"
#include "BoxColliderComponent.h"

#include "EventDispatcher.h"
#include "Renderer.h"
#include "ServiceLocator.h"

BoxColliderComponent::BoxColliderComponent(dae::GameObject& parent, bool isStatic, bool blockOnCollision, float width, float height, bool debugRender):
CollisionComponent(parent,isStatic,blockOnCollision,width,height),
m_DebugRenderingActive(debugRender)
{
	ServiceLocator::GetCollisionService().RegisterCollisionObject(this, new BoxShape{width,height});
	m_Location = GetParent()->GetLocalPosition() + glm::vec3(m_Offset, 0);
}

BoxColliderComponent::BoxColliderComponent(dae::GameObject& parent, bool isStatic, bool blockOnCollision,
	glm::vec2 size, glm::vec2 offset, bool debugRender):
CollisionComponent(parent, isStatic, blockOnCollision, size,offset),
m_DebugRenderingActive(debugRender)
{
	ServiceLocator::GetCollisionService().RegisterCollisionObject(this, new BoxShape{ size.x,size.y });
	m_Location = GetParent()->GetLocalPosition() + glm::vec3(m_Offset, 0);
}

BoxColliderComponent::~BoxColliderComponent()
{
	ServiceLocator::GetCollisionService().UnRegisterCollisionObject(this);
}

bool BoxColliderComponent::WouldCollide(const glm::vec3 position)
{
	glm::vec3 myColliderPos = position + glm::vec3(m_Offset, 0);
	const glm::vec2 mySize = GetSize();

	auto& collisionComponents = ServiceLocator::GetCollisionService().GetCollisionComponents();

	for (auto* other : collisionComponents)
	{
		if (other == this || !other->GetIsBlocking()) continue;

		const glm::vec2 otherPos = other->GetLocalColliderPosition();
		const glm::vec2 otherSize = other->GetSize();

		const float tolerance = 0.1f;
		float shrinkX = otherSize.x * tolerance;
		float shrinkY = otherSize.y * tolerance;

		if (IsCollidingAABB(myColliderPos.x, myColliderPos.y,
			otherPos.x + shrinkX,
			otherPos.y + shrinkY,
			otherSize.x - 2 * shrinkX,
			otherSize.y - 2 * shrinkY))
		{
			return true;
		}
	}
	return false;
}

bool BoxColliderComponent::IsCollidingAABB(const float ax, const float ay, const float bx, const float by, const float bw, const float bh) const
{
	return (ax < bx + bw) &&
		(ax + m_Size.x > bx) &&
		(ay < by + bh) &&
		(ay + m_Size.y > by);
}

void BoxColliderComponent::FixedUpdate()
{
	Component::FixedUpdate();

	if (m_IsStatic) return;

	m_Location = GetParent()->GetLocalPosition() + glm::vec3(m_Offset, 0);

	auto& collisionComponents = ServiceLocator::GetCollisionService().GetCollisionComponents();
	auto& collisionShapes = ServiceLocator::GetCollisionService().GetCollisionShapes();

	bool hasCollidedWithAnyObj{ false };

	for (int idx{}; idx < collisionComponents.size(); idx++)
	{
		const glm::vec2 otherObjPos = collisionComponents[idx]->GetLocalColliderPosition();
		const auto* collisionShape = collisionShapes[idx];
		const bool isBlockingCollision = collisionComponents[idx]->GetIsBlocking();

		if (this == collisionComponents[idx])
		{
			continue;
		}

		const glm::vec2 size = collisionShape->GetDescriptor().box.size;
		if (IsCollidingAABB(m_Location.x, m_Location.y,
			otherObjPos.x, otherObjPos.y, size.x, size.y))
		{
			if (isBlockingCollision)
			{
				GetParent()->SetLocalPosition(m_LastSafePos);
				hasCollidedWithAnyObj = true;
			}
			else
			{
				collisionComponents[idx]->OnEnterEvent();
			}
		}
	}

	if (!hasCollidedWithAnyObj)
	{
		m_LastSafePos = GetParent()->GetLocalPosition();
	}
	
}

void BoxColliderComponent::Render()
{
	if (m_DebugRenderingActive)
	{
		Component::Render();
		dae::Renderer::GetInstance().RenderDebugRect(m_Size.x,m_Size.y, m_Location.x, m_Location.y);
	}

}

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

bool BoxColliderComponent::IsCollidingInDirection(const glm::vec2 direction, float checkDistance) const
{
	auto owner = GetParent();
	auto pos = owner->GetWorldPosition();

	// Only check a small distance ahead (adjust this value as needed)
	float actualCheckDistance = std::min(checkDistance, 2.0f); // Check just 2 units ahead
	glm::vec2 newPos = glm::vec2(pos.x, pos.y) + direction * actualCheckDistance;

	SDL_FRect futureBounds{ newPos.x, newPos.y, m_Size.x, m_Size.y };

	auto& collisionComponents = ServiceLocator::GetCollisionService().GetCollisionComponents();
	auto& collisionShapes = ServiceLocator::GetCollisionService().GetCollisionShapes();

	for (int idx{}; idx < collisionComponents.size(); idx++)
	{
		if (this == collisionComponents[idx]) continue;

		const glm::vec2 otherObjPos = collisionComponents[idx]->GetLocalColliderPosition();
		const auto* collisionShape = collisionShapes[idx];
		const bool isBlockingCollision = collisionComponents[idx]->GetIsBlocking();

		const glm::vec2 size = collisionShape->GetDescriptor().box.size;

		if (IsCollidingAABB(futureBounds.x, futureBounds.y,
			otherObjPos.x, otherObjPos.y, size.x, size.y))
		{
			if (isBlockingCollision)
			{
				return true;
			}
			collisionComponents[idx]->OnEnterEvent();
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

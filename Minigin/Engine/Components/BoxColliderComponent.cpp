#include "BoxColliderComponent.h"

#include "EventDispatcher.h"
#include "Renderer.h"
#include "ServiceLocator.h"

BoxColliderComponent::BoxColliderComponent(dae::GameObject& parent, bool isStatic, bool blockOnCollision, float width, float height, bool debugRender):
Component(parent),
m_IsStatic{isStatic},
m_BlockOnCollision(blockOnCollision),
m_DebugRenderingActive(debugRender),
m_Size(width,height)
{
	ServiceLocator::GetCollisionService().RegisterCollisionObject(GetParent(), new BoxShape{width,height},blockOnCollision);
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

	auto& collisionObjs = ServiceLocator::GetCollisionService().GetCollisionObjects();
	auto& collisionShapes = ServiceLocator::GetCollisionService().GetCollisionShapes();
	auto& collisionObjIsBlockingShape = ServiceLocator::GetCollisionService().GetIsBlockingCollisions();

	bool hasCollidedWithAnyObj{ false };

	for (int idx{}; idx < collisionObjs.size(); idx++)
	{
		const glm::vec2 currentObjPos = GetParent()->GetLocalPosition();
		const glm::vec2 otherObjPos = collisionObjs[idx]->GetLocalPosition();
		const auto* collisionShape = collisionShapes[idx];
		const bool isBlockingCollision = collisionObjIsBlockingShape[idx];

		if (GetParent() == collisionObjs[idx])
		{
			continue;
		}

		const glm::vec2 size = collisionShape->GetDescriptor().box.size;
		if (isBlockingCollision)
		{
			if (IsCollidingAABB(currentObjPos.x, currentObjPos.y,
				otherObjPos.x, otherObjPos.y, size.x, size.y))
			{
				GetParent()->SetLocalPosition(m_LastSafePos);
				hasCollidedWithAnyObj = true;
			}
		}
		else
		{

		}
		
	}

	if (!hasCollidedWithAnyObj)
	{
		m_LastSafePos = GetParent()->GetLocalPosition();
	}
	
}

void BoxColliderComponent::AddOnEnterEvent(const Event& event) const
{
	EventDispatcher::GetInstance().Dispatch(event, GetParent());
}

void BoxColliderComponent::AddWhileInEvent(const Event& event) const
{
	EventDispatcher::GetInstance().Dispatch(event, GetParent());
}

void BoxColliderComponent::AddWhileOutEvent(const Event& event) const
{
	EventDispatcher::GetInstance().Dispatch(event, GetParent());
}

void BoxColliderComponent::AddOnExitEvent(const Event& event) const
{
	EventDispatcher::GetInstance().Dispatch(event, GetParent());
}

void BoxColliderComponent::Render()
{
	if (m_DebugRenderingActive)
	{
		Component::Render();
		auto pos = GetParent()->GetLocalPosition();
		dae::Renderer::GetInstance().RenderDebugRect(m_Size.x,m_Size.y, pos.x, pos.y);
	}

}

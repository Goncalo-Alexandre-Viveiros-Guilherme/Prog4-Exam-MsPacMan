#include "BoxCollisionService.h"

#include "GameObject.h"

BoxCollisionService::BoxCollisionService()
= default;

BoxCollisionService::~BoxCollisionService()
= default;

void BoxCollisionService::RegisterCollisionObject(CollisionComponent* collisionComponent, Shape* shape)
{
	m_CollisionComponents.emplace_back(collisionComponent);
	m_CollisionShapes.emplace_back(shape);
}

void BoxCollisionService::UnRegisterCollisionObject(CollisionComponent* collisionComponent)
{
    auto it = std::ranges::find(m_CollisionComponents, collisionComponent);

    if (it != m_CollisionComponents.end())
    {
        size_t index = std::distance(m_CollisionComponents.begin(), it);

        m_CollisionComponents.erase(it);
        m_CollisionShapes.erase(m_CollisionShapes.begin() + index);
    }
}

std::vector<CollisionComponent*>& BoxCollisionService::GetCollisionComponents()
{
	return m_CollisionComponents;
}

std::vector<Shape*>& BoxCollisionService::GetCollisionShapes()
{
	return m_CollisionShapes;
}

std::vector<bool>& BoxCollisionService::GetIsBlockingCollisions()
{
	return m_IsBlockingCollisions;
}


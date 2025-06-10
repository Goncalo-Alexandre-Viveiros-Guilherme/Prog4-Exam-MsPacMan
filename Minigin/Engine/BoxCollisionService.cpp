#include "BoxCollisionService.h"

#include "BoxColliderComponent.h"
#include "GameObject.h"

BoxCollisionService::BoxCollisionService()
= default;

BoxCollisionService::~BoxCollisionService()
= default;

void BoxCollisionService::RegisterCollisionObject(dae::GameObject* gameObj, Shape* boxShape,bool isBlocking)
{
	m_CollisionObjects.emplace_back(gameObj);
	m_CollisionShape.emplace_back(boxShape);
	m_IsBlockingCollisions.emplace_back(isBlocking);
}

std::vector<dae::GameObject*>& BoxCollisionService::GetCollisionObjects()
{
	return m_CollisionObjects;
}

std::vector<Shape*>& BoxCollisionService::GetCollisionShapes()
{
	return m_CollisionShape;
}

std::vector<bool>& BoxCollisionService::GetIsBlockingCollisions()
{
	return m_IsBlockingCollisions;
}


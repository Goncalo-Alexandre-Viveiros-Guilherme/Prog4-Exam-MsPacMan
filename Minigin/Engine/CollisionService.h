#ifndef COLLISIONSERVICE_H
#define COLLISIONSERVICE_H
#include <vector>
#include <Shapes.h>

#include "BoxColliderComponent.h"
#include "CollisionComponent.h"


class CollisionService
{

public:
	virtual ~CollisionService() = default;

	virtual void RegisterCollisionObject(CollisionComponent* collisionComponent,Shape* shape) = 0;
	virtual void UnRegisterCollisionObject(CollisionComponent* boxColliderComponent) = 0;
	virtual std::vector<CollisionComponent*>& GetCollisionComponents() = 0;
	virtual std::vector<Shape*>& GetCollisionShapes() = 0;
	virtual std::vector<bool>& GetIsBlockingCollisions() = 0;
};
#endif // COLLISIONSERVICE_H

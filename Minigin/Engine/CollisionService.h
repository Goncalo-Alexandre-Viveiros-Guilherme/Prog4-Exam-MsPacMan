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

	virtual void RegisterCollisionObject(CollisionComponent* collisionComponent,std::unique_ptr<Shape> shape) = 0;
	virtual void UnRegisterCollisionObject(CollisionComponent* boxColliderComponent) = 0;
	virtual std::vector<CollisionComponent*>& GetCollisionComponents() = 0;
	virtual std::vector<std::unique_ptr<Shape>>& GetCollisionShapes() = 0;
	virtual std::vector<bool>& GetIsBlockingCollisions() = 0;
	virtual void Clear() = 0;
};
#endif // COLLISIONSERVICE_H

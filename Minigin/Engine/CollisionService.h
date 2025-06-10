#ifndef COLLISIONSERVICE_H
#define COLLISIONSERVICE_H
#include <vector>
#include <Shapes.h>



namespace dae
{
	class GameObject;
}


class CollisionService
{

public:
	virtual ~CollisionService() = default;

	virtual void RegisterCollisionObject(dae::GameObject* gameObj,Shape* shape, bool isBlocking) = 0;
	virtual std::vector<dae::GameObject*>& GetCollisionObjects() = 0;
	virtual std::vector<Shape*>& GetCollisionShapes() = 0;
	virtual std::vector<bool>& GetIsBlockingCollisions() = 0;
};
#endif // COLLISIONSERVICE_H

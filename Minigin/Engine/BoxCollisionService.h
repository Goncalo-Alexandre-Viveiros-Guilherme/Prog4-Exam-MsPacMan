#ifndef BOXCOLLISIONSERVICE_H
#define BOXCOLLISIONSERVICE_H	
#include "CollisionService.h"

class BoxCollisionService : public CollisionService
{
public:
	BoxCollisionService();
	~BoxCollisionService() override;

	virtual void RegisterCollisionObject(CollisionComponent* collisionComponent, std::unique_ptr<Shape> shape) override;
	virtual void UnRegisterCollisionObject(CollisionComponent* collisionComponent) override;
	virtual std::vector<CollisionComponent*>& GetCollisionComponents() override;
	virtual std::vector<std::unique_ptr<Shape>>& GetCollisionShapes() override;
	virtual std::vector<bool>& GetIsBlockingCollisions() override;

private:
	std::vector<CollisionComponent*> m_CollisionComponents;
	std::vector<std::unique_ptr<Shape>> m_CollisionShapes;
	std::vector<bool> m_IsBlockingCollisions;
};
#endif // BOXCOLLISIONSERVICE_H

#ifndef BOXCOLLISIONSERVICE_H
#define BOXCOLLISIONSERVICE_H	
#include "CollisionService.h"

class BoxCollisionService : public CollisionService
{
public:
	BoxCollisionService();
	virtual ~BoxCollisionService();
	virtual void RegisterCollisionObject(dae::GameObject* gameObj,Shape* boxShape, bool isBlocking) override;
	virtual std::vector<dae::GameObject*>& GetCollisionObjects() override;
	virtual std::vector<Shape*>& GetCollisionShapes() override;
	virtual std::vector<bool>& GetIsBlockingCollisions() override;

private:
	std::vector<dae::GameObject*> m_CollisionObjects;
	std::vector<Shape*> m_CollisionShape;
	std::vector<bool> m_IsBlockingCollisions;
};
#endif // BOXCOLLISIONSERVICE_H

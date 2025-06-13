#include "Component.h"
#include "vec3.hpp"

class ResetPositionComponent : public Component
{
public:
	ResetPositionComponent(dae::GameObject* parent, const glm::vec3 pos):
	Component(parent),
	m_PosToSave(pos)
	{
		EventDispatcher::GetInstance().AddListener<ResetEntityPosEvent>
			(nullptr, [this](const ResetEntityPosEvent& event)
				{
					SetParentObjToSavedPos();
					event;
				}
			);
	}

	void SetParentObjToSavedPos() const
	{
		GetParent()->GetComponent<MoveComponent>()->SetDesiredDirection(None);
		GetParent()->SetLocalPosition(m_PosToSave);
	}

	~ResetPositionComponent() = default;
private:
	glm::vec3 m_PosToSave;
};
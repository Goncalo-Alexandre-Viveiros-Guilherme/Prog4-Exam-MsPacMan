#include "FSM.h"
#include "vec2.hpp"

class MoveCommand;
class MoveComponent;

namespace dae
{
	class GameObject;
}

namespace FSM
{
	class ChaseState : public State
	{
	public:
		ChaseState(dae::GameObject* mainAgent);
		~ChaseState() = default;

		virtual void OnEnter() override;
		virtual void Update() override {}
		virtual void OnExit() override {}


	protected:
		MoveComponent* m_MoveComponent	{ nullptr };
		dae::GameObject* m_Target		{ nullptr };
		dae::GameObject* m_MainAgent	{ nullptr };
		int m_LastCellPosX				{ 0 };
		int m_LastCellPosY				{ 0 };
	};

	class BlinkyChaseState : public ChaseState
	{
	public:
		BlinkyChaseState(dae::GameObject* mainAgent, dae::GameObject* objectToChase);
		~BlinkyChaseState() = default;

		virtual void OnEnter() override{}
		virtual void Update() override;
		virtual void OnExit() override{}

	};
}

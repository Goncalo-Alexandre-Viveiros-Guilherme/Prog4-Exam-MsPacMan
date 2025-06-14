#include "Commands.h"
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
		// Add to ChaseState class
	protected:
		glm::ivec2 m_LastGridPos{ -1, -1 };
		bool m_HasRecalculatedThisCell = false;
	};

	class BlinkyChaseState : public ChaseState
	{
	public:
		BlinkyChaseState(dae::GameObject* mainAgent, dae::GameObject* objectToChase);
		~BlinkyChaseState() = default;

		virtual void OnEnter() override{}
		virtual void Update() override;
		DesiredDirection GetReverseDirection(DesiredDirection dir);
		virtual void OnExit() override{}

	};

	class BlinkyFrightenedState : public State
	{
	public:
		BlinkyFrightenedState(dae::GameObject* mainAgent) { mainAgent; }
		~BlinkyFrightenedState() = default;

		virtual void OnEnter() override {}
		virtual void Update() override{}
		DesiredDirection GetReverseDirection(DesiredDirection dir) { dir; }
		virtual void OnExit() override {}

	};
}

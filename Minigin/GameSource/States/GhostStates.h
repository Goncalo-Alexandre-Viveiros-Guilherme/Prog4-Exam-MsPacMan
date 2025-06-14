#ifndef GHOSTSTATES_H
#define GHOSTSTATES_H
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
		ChaseState(dae::GameObject* mainAgent, std::vector<glm::vec2> forbiddenCells);
		~ChaseState() = default;

		virtual void OnEnter() override;
		virtual void Update() override {}
		virtual void OnExit() override {}


	protected:
		MoveComponent* m_MoveComponent	{ nullptr };
		dae::GameObject* m_Target		{ nullptr };
		dae::GameObject* m_MainAgent	{ nullptr };
		std::vector<glm::vec2> m_ForbiddenCells{};
		// Add to ChaseState class
	protected:
		glm::ivec2 m_LastGridPos{ -1, -1 };
		bool m_HasRecalculatedThisCell = false;
	};

	class BlinkyChaseState : public ChaseState
	{
	public:
		BlinkyChaseState(dae::GameObject* mainAgent, dae::GameObject* objectToChase, std::vector<glm::vec2> forbiddenCells);
		~BlinkyChaseState() = default;

		virtual void OnEnter() override;
		virtual void Update() override;
		virtual void OnExit() override{}

	};

	class BlinkyFrightenedState : public State
	{
	public:
		BlinkyFrightenedState(dae::GameObject* mainAgent, glm::vec2 targetPos);
		~BlinkyFrightenedState() = default;

		virtual void OnEnter() override;
		virtual void Update() override;

		virtual void OnExit() override;

	private:
		MoveComponent* m_MoveComponent{ nullptr };
		glm::vec2 m_Target{ };
		dae::GameObject* m_MainAgent{ nullptr };
		glm::ivec2 m_LastGridPos{ -1, -1 };
		bool m_HasRecalculatedThisCell = false;

	};

	class HasPowerPelletBeenEaten : public Condition {
	public:
		HasPowerPelletBeenEaten();
		virtual ~HasPowerPelletBeenEaten() = default;
		bool Evaluate() override;

		void SetHasPowerPelletBeenEaten(bool value);

	private:
		bool m_HasPowerPelletBeenEaten{false};
	};

	class TimerIsWeak : public Condition {
	public:
		TimerIsWeak();
		virtual ~TimerIsWeak() = default;
		bool Evaluate() override;


	private:
		float m_HowLongHasBeenWeak{ 0.0f };
	};
}
#endif // GHOSTSTATES_H

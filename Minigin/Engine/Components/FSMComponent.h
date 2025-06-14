#ifndef FSMCOMPONENT_H
#define FSMCOMPONENT_H
#include "Component.h"
#include "Events.h"
#include "FSM.h"

class FSMComponent final : public Component
{
public:
	FSMComponent(dae::GameObject* parent, std::unique_ptr<FSM::State> initialState);
	~FSMComponent() override = default;

	void Update() override;

	void AddTransition(FSM::State* fromState, std::unique_ptr<FSM::State> toState, std::unique_ptr<FSM::Condition> condition) const;
	void AddTransition(FSM::State* fromState, FSM::State* toState, std::unique_ptr<FSM::Condition> condition) const;

	FSM::State* GetCurrentState() const { return m_FSM->GetCurrentState(); }

private:
	std::unique_ptr<FSM::FiniteStateMachine> m_FSM;
};
#endif // FSMCOMPONENT_H

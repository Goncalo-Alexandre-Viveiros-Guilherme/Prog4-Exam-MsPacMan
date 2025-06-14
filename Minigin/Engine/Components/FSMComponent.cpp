#include "FSMComponent.h"

FSMComponent::FSMComponent(dae::GameObject* parent, std::unique_ptr<FSM::State> initialState): Component(parent)
{
	m_FSM = std::make_unique<FSM::FiniteStateMachine>(std::move<>(initialState));
}

void FSMComponent::Update()
{
	Component::Update();
	m_FSM->Update();
}

void FSMComponent::AddTransition(FSM::State* fromState, std::unique_ptr<FSM::State> toState,
	std::unique_ptr<FSM::Condition> condition) const
{
	m_FSM->AddTransition(fromState, std::move<>(toState), std::move<>(condition));
}

void FSMComponent::AddTransition(FSM::State* fromState, FSM::State* toState,
	std::unique_ptr<FSM::Condition> condition) const
{
	m_FSM->AddTransition(fromState, toState, std::move<>(condition));
}

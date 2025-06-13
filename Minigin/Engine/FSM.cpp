#include "FSM.h"

namespace FSM {

    FiniteStateMachine::FiniteStateMachine(std::unique_ptr<State> initialState)
        : m_CurrentState(initialState.get()) {
        m_OwnedStates.push_back(std::move(initialState));
    }

    void FiniteStateMachine::AddTransition(State* fromState,
        std::unique_ptr<State> toState,
        std::unique_ptr<Condition> condition) {
        State* rawToState = toState.get();
        m_OwnedStates.push_back(std::move(toState));

        m_Transitions[fromState].push_back(
            { std::move(condition), rawToState }
        );
    }

    void FiniteStateMachine::Update() {
        if (!m_CurrentState) return;

        auto it = m_Transitions.find(m_CurrentState);
        if (it == m_Transitions.end()) {
            m_CurrentState->Update();
            return;
        }

        for (auto& transition : it->second) {
            if (transition.Condition->Evaluate()) {
                m_CurrentState->Update();
                ChangeState(transition.TargetState);
                return;
            }
        }

        m_CurrentState->Update();
    }

    void FiniteStateMachine::ChangeState(State* newState) {
        if (m_CurrentState) {
            m_CurrentState->OnExit();
        }

        m_CurrentState = newState;

        if (m_CurrentState) {
            m_CurrentState->OnEnter();
        }
    }
}
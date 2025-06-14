#ifndef FSM_H
#define FSM_H

#include <memory>
#include <vector>
#include <unordered_map>

namespace FSM {
    class State {
    public:
        virtual ~State() = default;
        virtual void OnEnter() = 0;
        virtual void Update() = 0;
        virtual void OnExit() = 0;
    };

    class NullState: public State {
    public:
        virtual ~NullState() = default;
        void OnEnter() override {}
        void OnExit() override  {}
        void Update() override  {}
    };

    class Condition {
    public:
        virtual ~Condition() = default;
        virtual bool Evaluate() const = 0;
    };

    class AlwaysTrueCond : public Condition {
    public:
        virtual ~AlwaysTrueCond() = default;
        bool Evaluate() const override { return true; }  // Added const and override
    };

    class AlwaysFalseCond : public Condition {
    public:
        virtual ~AlwaysFalseCond() = default;
        virtual bool Evaluate() { return false;  }
    };

    class FiniteStateMachine {
    public:
        // Takes ownership of initial state
        explicit FiniteStateMachine(std::unique_ptr<State> initialState);

        // Takes ownership of both state and condition
        void AddTransition(State* fromState,
            std::unique_ptr<State> toState,
            std::unique_ptr<Condition> condition);

        void Update();
        State* GetCurrentState() const { return m_CurrentState; }

        void ChangeState(State* newState);
    private:
        struct Transition {
            std::unique_ptr<Condition> Condition;
            State* TargetState;
        };

        std::vector<std::unique_ptr<State>> m_OwnedStates;
        std::unordered_map<State*, std::vector<Transition>> m_Transitions;
        State* m_CurrentState{ nullptr };
    };
}
#endif
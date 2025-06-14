// MenuController.cpp
#include "MenuController.h"
#include "Commands.h"
#include "MsPacmanCode.h"

// States
class MenuController::NormalState : public FSM::State
{
public:
    NormalState(MenuController* controller) : m_Controller(controller) {}

    void OnEnter() override {
        m_Controller->m_NormalText->SetColor({ 255, 0, 0, 255 });
        m_Controller->m_VersusText->SetColor({ 255, 255, 255, 255 });
        m_Controller->m_CoopText->SetColor({ 255, 255, 255, 255 });
    }

    void Update() override {}  

    void OnExit() override {}

private:
    MenuController* m_Controller;
};

class MenuController::VersusState : public FSM::State
{
public:
    VersusState(MenuController* controller) : m_Controller(controller) {}

    void OnEnter() override {
        m_Controller->m_NormalText->SetColor({ 255, 255, 255, 255 });
        m_Controller->m_VersusText->SetColor({ 255, 0, 0, 255 });
        m_Controller->m_CoopText->SetColor({ 255, 255, 255, 255 });
    }

    void Update() override {} 

    void OnExit() override {}

private:
    MenuController* m_Controller;
};

class MenuController::CoopState : public FSM::State
{
public:
    CoopState(MenuController* controller) : m_Controller(controller) {}

    void OnEnter() override {
        m_Controller->m_NormalText->SetColor({ 255, 255, 255, 255 });
        m_Controller->m_VersusText->SetColor({ 255, 255, 255, 255 });
        m_Controller->m_CoopText->SetColor({ 255, 0, 0, 255 });
    }

    void Update() override {}  

    void OnExit() override {} 

private:
    MenuController* m_Controller;
};

class MoveUpCondition : public FSM::Condition
{
public:
    bool Evaluate() const override { return false; } 
};

class MoveDownCondition : public FSM::Condition
{
public:
    bool Evaluate() const override { return false; } 
};

// MenuController implementation
MenuController::MenuController(dae::GameObject* parent,
    TextComponent* normalText,
    TextComponent* versusText,
    TextComponent* coopText)
    : Component(parent)
    , m_NormalText(normalText)
    , m_VersusText(versusText)
    , m_CoopText(coopText)
{
    // Create states
    auto normalState = std::make_unique<NormalState>(this);
    auto versusState = std::make_unique<VersusState>(this);
    auto coopState = std::make_unique<CoopState>(this);

    // Create FSM with initial state
    m_FSM = new FSM::FiniteStateMachine(std::move(normalState));

    // Add transitions
    m_FSM->AddTransition(
        m_FSM->GetCurrentState(),
        std::move(versusState),
        std::make_unique<MoveDownCondition>()
    );

    m_FSM->AddTransition(
        m_FSM->GetCurrentState(),
        std::move(coopState),
        std::make_unique<MoveDownCondition>()
    );
}

void MenuController::Update()
{
    m_FSM->Update();
}

void MenuController::MoveUp()
{
    // Manually trigger state transitions
    if (dynamic_cast<CoopState*>(m_FSM->GetCurrentState())) {
        m_FSM->ChangeState(new VersusState(this));
    }
    else if (dynamic_cast<VersusState*>(m_FSM->GetCurrentState())) {
        m_FSM->ChangeState(new NormalState(this));
    }
}

void MenuController::MoveDown()
{
    // Manually trigger state transitions
    if (dynamic_cast<NormalState*>(m_FSM->GetCurrentState())) {
        m_FSM->ChangeState(new VersusState(this));
    }
    else if (dynamic_cast<VersusState*>(m_FSM->GetCurrentState())) {
        m_FSM->ChangeState(new CoopState(this));
    }
}

void MenuController::SelectCurrent()
{
    // Handle selection based on current state
    if (dynamic_cast<NormalState*>(m_FSM->GetCurrentState())) 
    {
        MsPacmanCode msPacmanCode{ GameModes::Normal, };
		msPacmanCode.LoadGameCode("level1.csv");
    }
    else if (dynamic_cast<VersusState*>(m_FSM->GetCurrentState())) 
    {
        MsPacmanCode msPacmanCode{ GameModes::Versus, };
        msPacmanCode.LoadGameCode("level1.csv");
    }
    else if (dynamic_cast<CoopState*>(m_FSM->GetCurrentState())) 
    {
        MsPacmanCode msPacmanCode{ GameModes::CoOp, };
        msPacmanCode.LoadGameCode("level1.csv");
    }
}
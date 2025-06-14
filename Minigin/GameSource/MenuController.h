#pragma once
#include "Component.h"
#include "FSM.h"
#include "TextComponent.h"

class MenuController : public Component
{
public:
    MenuController(dae::GameObject* parent,
        TextComponent* normalText,
        TextComponent* versusText,
        TextComponent* coopText);
    ~MenuController();

    void Update() override;
    void SelectCurrent();
    void MoveUp();
    void MoveDown();

private:
    class NormalState;
    class VersusState;
    class CoopState;

    VersusState* m_VersusState;
    NormalState* m_NormalState;
    CoopState* m_CoopState;
    FSM::FiniteStateMachine* m_FSM;
    TextComponent* m_NormalText;
    TextComponent* m_VersusText;
    TextComponent* m_CoopText;
};
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
    ~MenuController() = default;

    void Update() override;
    void SelectCurrent();
    void MoveUp();
    void MoveDown();

private:
    class NormalState;
    class VersusState;
    class CoopState;

    FSM::FiniteStateMachine* m_FSM;
    TextComponent* m_NormalText;
    TextComponent* m_VersusText;
    TextComponent* m_CoopText;
};
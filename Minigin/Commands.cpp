#include "Commands.h"
#include "GameObject.h"
#include <EngineTime.h>

MoveCommand::MoveCommand(float speedX,float speedY) :m_SpeedX(speedX),m_SpeedY(speedY)
{
}

void MoveCommand::execute(dae::GameObject* actor)
{
    auto& pos = actor->GetLocalPosition();
    actor->SetLocalPosition(pos.x + (m_SpeedX * Time::GetInstance().GetDeltaTime()), pos.y + (m_SpeedY * Time::GetInstance().GetDeltaTime()));
}
#include "Commands.h"
#include "GameObject.h"
#include <EngineTime.h>

MoveCommand::MoveCommand(float speedX,float speedY, dae::GameObject* actor) :m_SpeedX(speedX),m_SpeedY(speedY),m_Actor(actor)
{
}

void MoveCommand::execute()
{
    auto& pos = m_Actor->GetLocalPosition();
    m_Actor->SetLocalPosition(pos.x + (m_SpeedX * Time::GetInstance().GetDeltaTime()), pos.y + (m_SpeedY * Time::GetInstance().GetDeltaTime()));
}
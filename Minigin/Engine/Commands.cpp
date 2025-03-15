#include "Commands.h"
#include "GameObject.h"
#include <EngineTime.h>

#include "HealthComponent.h"

MoveCommand::MoveCommand(float speedX,float speedY, dae::GameObject* actor) :m_SpeedX(speedX),m_SpeedY(speedY),m_Actor(actor)
{
}

void MoveCommand::Execute()
{
    auto& pos = m_Actor->GetLocalPosition();
    m_Actor->SetLocalPosition(pos.x + (m_SpeedX * Time::GetInstance().GetDeltaTime()), pos.y + (m_SpeedY * Time::GetInstance().GetDeltaTime()));
}

AddHealthCommand::AddHealthCommand(float AmountToAdd, HealthComponent* healthComponent): m_ValueToAdd(AmountToAdd),m_HealthComponent(healthComponent)
{
}

void AddHealthCommand::Execute()
{
    m_HealthComponent->AddToHealth(m_ValueToAdd);
}

#include "Commands.h"
#include "HealthComponent.h"
#include "MoveComponent.h"
#include "PointsComponent.h"

MoveCommand::MoveCommand(float speedX,float speedY, MoveComponent* moveComponent): m_SpeedY(speedY),m_SpeedX(speedX), m_MoveComponent(moveComponent)
{
}

void MoveCommand::Execute()
{
    m_MoveComponent->SetSpeed(m_SpeedX, m_SpeedY);
}

AddHealthCommand::AddHealthCommand(float amountToAdd, HealthComponent* healthComponent): m_ValueToAdd(amountToAdd),m_HealthComponent(healthComponent)
{
}

void AddHealthCommand::Execute()
{
    m_HealthComponent->AddToHealth(m_ValueToAdd);
}

AddPointsCommand::AddPointsCommand(float amountToAdd, PointsComponent* pointsComponent) : m_ValueToAdd(amountToAdd), m_PointsComponent(pointsComponent)
{
}

void AddPointsCommand::Execute()
{
    m_PointsComponent->AddToPoints(m_ValueToAdd);
}

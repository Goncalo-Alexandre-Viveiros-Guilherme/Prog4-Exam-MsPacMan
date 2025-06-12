#include "Commands.h"
#include "HealthComponent.h"
#include "MoveComponent.h"
#include "PointsComponent.h"

MoveCommand::MoveCommand(const float speed, const DesiredDirection desiredDirection, MoveComponent* moveComponent):
m_Speed(speed),
m_MoveComponent(moveComponent),
m_DesiredDirection(desiredDirection)
{
    m_MoveComponent->SetSpeed(m_Speed);
}

void MoveCommand::Execute()
{
    m_MoveComponent->SetDesiredDirection(m_DesiredDirection);
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

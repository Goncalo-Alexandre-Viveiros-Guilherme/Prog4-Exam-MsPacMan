#include "Commands.h"
#include "HealthComponent.h"
#include "MoveComponent.h"
#include "PointsComponent.h"
#include "ServiceLocator.h"
#include "WinConditionManager.h"

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

void MoveCommand::SetDesiredDirection(const DesiredDirection desiredDirection)
{
    m_DesiredDirection = desiredDirection;
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

MuteCommand::MuteCommand(): m_IsMuted(false)
{
}

void MuteCommand::Execute()
{
	if (m_IsMuted)
	{
		ServiceLocator::GetAudioService().SetMusicVolume(100);
        ServiceLocator::GetAudioService().SetAllAudioVolume(100);

		m_IsMuted = false;
	}
	else
	{
		ServiceLocator::GetAudioService().SetMusicVolume(0);
		ServiceLocator::GetAudioService().SetAllAudioVolume(0);

		m_IsMuted = true;
	}
}

void SkipLevel::Execute()
{
	WinConditionManager::GetInstance().NextLevel();
}

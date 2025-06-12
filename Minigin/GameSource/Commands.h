#pragma once


enum DesiredDirection : int;

namespace dae
{ 
class GameObject;
}
class HealthComponent;
class PointsComponent;
class MoveComponent;

class Command
{
public:
	virtual ~Command() = default;
	virtual void Execute() = 0;
};

class MoveCommand : public Command
{
public:
	MoveCommand(float speed, DesiredDirection desiredDirection ,MoveComponent* moveComponent);
	void Execute() override;

private:
	float m_Speed;
	MoveComponent* m_MoveComponent;
	DesiredDirection m_DesiredDirection;
};

class AddHealthCommand : public Command
{
public:
	AddHealthCommand(float amountToAdd,HealthComponent* healthComponent);
	void Execute() override;

private:
	float m_ValueToAdd;
	HealthComponent* m_HealthComponent;
};

class AddPointsCommand : public Command
{
public:
	AddPointsCommand(float amountToAdd, PointsComponent* pointsComponent);
	void Execute() override;

private:
	float m_ValueToAdd;
	PointsComponent* m_PointsComponent;
};
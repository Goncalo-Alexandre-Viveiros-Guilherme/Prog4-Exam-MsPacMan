#pragma once

class HealthComponent;

namespace dae
{ 
class GameObject;
}

class Command
{
public:
	virtual ~Command() {}
	virtual void Execute() = 0;
};

class MoveCommand : public Command
{
public:
	MoveCommand(float speedX, float speedY, dae::GameObject* actor);
	void Execute() override;

private:
	float m_SpeedY;
	float m_SpeedX;
	dae::GameObject* m_Actor;
};

class AddHealthCommand : public Command
{
public:
	AddHealthCommand(float AmountToAdd,HealthComponent* healthComponent);
	void Execute() override;

private:
	float m_ValueToAdd;
	HealthComponent* m_HealthComponent;
};
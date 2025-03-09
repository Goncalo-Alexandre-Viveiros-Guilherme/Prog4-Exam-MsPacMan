#pragma once

namespace dae
{ 
class GameObject;
}

class Command
{
public:
	virtual ~Command() {}
	virtual void execute() = 0;
};

class MoveCommand : public Command
{
public:
	MoveCommand(float speedX, float speedY, dae::GameObject* actor);
	virtual void execute();

private:
	float m_SpeedY;
	float m_SpeedX;
	dae::GameObject* m_Actor;
};
#pragma once

namespace dae
{ 
class GameObject;
}

class Command
{
public:
	virtual ~Command() {}
	virtual void execute(dae::GameObject* actor) = 0;
};

class MoveCommand : public Command
{
public:
	MoveCommand(float speedX, float speedY);
	virtual void execute(dae::GameObject* actor);

private:
	float m_SpeedY;
	float m_SpeedX;
};
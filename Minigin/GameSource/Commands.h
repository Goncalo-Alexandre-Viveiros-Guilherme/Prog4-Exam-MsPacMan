#pragma once
#include "MenuController.h"


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

	void SetDesiredDirection(DesiredDirection desiredDirection);

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

class MuteCommand : public Command
{
public:
	MuteCommand();
	void Execute() override;

private:
	bool m_IsMuted;
};


class SkipLevel : public Command
{
public:
	SkipLevel() = default;
	void Execute() override;
};

class MenuMoveUpCommand : public Command
{
public:
	MenuMoveUpCommand(MenuController* menu) : m_Menu(menu) {}
	void Execute() override { m_Menu->MoveUp(); }
private:
	MenuController* m_Menu;
};

class MenuMoveDownCommand : public Command
{
public:
	MenuMoveDownCommand(MenuController* menu) : m_Menu(menu) {}
	void Execute() override { m_Menu->MoveDown(); }
private:
	MenuController* m_Menu;
};

class MenuSelectCommand : public Command
{
public:
	MenuSelectCommand(MenuController* menu) : m_Menu(menu) {}
	void Execute() override { m_Menu->SelectCurrent(); }
private:
	MenuController* m_Menu;
};
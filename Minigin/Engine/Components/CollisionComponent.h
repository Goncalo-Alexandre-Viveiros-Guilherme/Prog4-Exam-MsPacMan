#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H

#include "Component.h"
#include "EventDispatcher.h"
#include "vec2.hpp"
#include "vec3.hpp"

class CollisionComponent : public Component
{
public:
	CollisionComponent(dae::GameObject& parent, bool isStatic, bool blockOnCollision, float width, float height):
	Component(parent),
	m_IsStatic{ isStatic },
	m_BlockOnCollision(blockOnCollision),
	m_Size(width, height)
	{}

	CollisionComponent(dae::GameObject& parent, bool isStatic, bool blockOnCollision, glm::vec2 size, glm::vec2 offset):
	Component(parent),
	m_IsStatic{ isStatic },
	m_BlockOnCollision(blockOnCollision),
	m_Size(size.x, size.y),
	m_Offset(offset)
	{
		
	}

	void FixedUpdate() override{}

	virtual void AddOnEnterEvent(std::unique_ptr<Event> eventToAdd)
	{
		m_OnEnterEvents.emplace_back(std::move(eventToAdd));
	}

	virtual void AddWhileInEvent(std::unique_ptr<Event> eventToAdd)
	{
		m_WhileInEvents.emplace_back(std::move(eventToAdd));
	}

	virtual void AddWhileOutEvent(std::unique_ptr<Event> eventToAdd)
	{
		m_WhileOutEvents.emplace_back(std::move(eventToAdd));
	}

	virtual void AddOnExitEvent(std::unique_ptr<Event> eventToAdd)
	{
		m_OnExitEvents.emplace_back(std::move(eventToAdd));
	}

	void OnEnterEvent() const
	{
		for (auto& onEnterEvent : m_OnEnterEvents)
		{
			EventDispatcher::GetInstance().Dispatch(*onEnterEvent, GetParent());
		}
	}

	void OnExitEvent() const
	{
		for (auto& onExitEvent : m_OnExitEvents)
		{
			EventDispatcher::GetInstance().Dispatch(*onExitEvent, GetParent());
		}
	}

	void WhileInEvent() const
	{
		for (auto& whileInEvent : m_WhileInEvents)
		{
			EventDispatcher::GetInstance().Dispatch(*whileInEvent, GetParent());
		}
	}

	void WhileOutEvent() const
	{
		for (auto& whileOutEvent : m_WhileOutEvents)
		{
			EventDispatcher::GetInstance().Dispatch(*whileOutEvent, GetParent());
		}
	}

	void Render() override{}

	virtual bool GetIsBlocking() const { return m_BlockOnCollision; }

	virtual glm::vec2 GetLocalColliderPosition() const { return m_Location; }

protected:
	bool m_IsStatic = false;
	bool m_BlockOnCollision = true;
	glm::vec2 m_Location{};
	glm::vec2 m_Size{};
	glm::vec2 m_Offset{};
	glm::vec3 m_LastSafePos{};
	std::vector<std::unique_ptr<Event>> m_OnEnterEvents{};
	std::vector<std::unique_ptr<Event>> m_OnExitEvents{};
	std::vector<std::unique_ptr<Event>> m_WhileInEvents{};
	std::vector<std::unique_ptr<Event>> m_WhileOutEvents{};
};
#endif // COLLISIONCOMPONENT_H

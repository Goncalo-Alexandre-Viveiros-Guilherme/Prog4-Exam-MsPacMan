#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H

#include <map>

#include "Component.h"
#include "EventDispatcher.h"
#include "vec2.hpp"
#include "vec3.hpp"

class CollisionComponent : public Component
{
public:
	CollisionComponent(dae::GameObject* parent, bool isStatic, bool blockOnCollision, float width, float height):
	Component(parent),
	m_IsStatic{ isStatic },
	m_BlockOnCollision(blockOnCollision),
	m_Size(width, height)
	{}

	CollisionComponent(dae::GameObject* parent, bool isStatic, bool blockOnCollision, glm::vec2 size, glm::vec2 offset):
	Component(parent),
	m_IsStatic{ isStatic },
	m_BlockOnCollision(blockOnCollision),
	m_Size(size.x, size.y),
	m_Offset(offset)
	{
		
	}

	virtual ~CollisionComponent() {
		// Clear all event vectors
		m_OnEnterEvents.clear();
		m_OnExitEvents.clear();
		m_WhileInEvents.clear();
		m_WhileOutEvents.clear();
	}

	void FixedUpdate() override{}

	virtual bool WouldCollide(glm::vec3 position) = 0;

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

	virtual void AddOnEnterEvent(std::unique_ptr<Event> eventToAdd,dae::GameObject* objectToTriggerEvent)
	{
		m_OnEnterKeyEvents[objectToTriggerEvent].emplace_back(std::move(eventToAdd));
	}

	virtual void AddWhileInEvent(std::unique_ptr<Event> eventToAdd, dae::GameObject* objectToTriggerEvent)
	{
		m_WhileInKeyEvents[objectToTriggerEvent].emplace_back(std::move(eventToAdd));
	}

	virtual void AddWhileOutEvent(std::unique_ptr<Event> eventToAdd, dae::GameObject* objectToTriggerEvent)
	{
		m_WhileOutKeyEvents[objectToTriggerEvent].emplace_back(std::move(eventToAdd));
	}

	virtual void AddOnExitEvent(std::unique_ptr<Event> eventToAdd, dae::GameObject* objectToTriggerEvent)
	{
		m_OnExitKeyEvents[objectToTriggerEvent].emplace_back(std::move(eventToAdd));
	}

	void OnEnterEvent(dae::GameObject* otherGameObject) const
	{
		for (auto& onEnterEvent : m_OnEnterEvents)
		{
			EventDispatcher::GetInstance().Dispatch(*onEnterEvent, GetParent());
		}

		if (auto it = m_OnEnterKeyEvents.find(otherGameObject); it != m_OnEnterKeyEvents.end())
		{
			for (auto& event : it->second)
			{
				EventDispatcher::GetInstance().Dispatch(*event, GetParent());
			}
		}
	}

	void OnExitEvent(dae::GameObject* otherGameObject) const
	{
		for (auto& onEnterEvent : m_OnEnterEvents)
		{
			EventDispatcher::GetInstance().Dispatch(*onEnterEvent, GetParent());
		}

		if (auto it = m_OnEnterKeyEvents.find(otherGameObject); it != m_OnEnterKeyEvents.end())
		{
			for (auto& event : it->second)
			{
				EventDispatcher::GetInstance().Dispatch(*event, GetParent());
			}
		}
	}

	void WhileInEvent(dae::GameObject* otherGameObject) const
	{
		for (auto& onEnterEvent : m_OnEnterEvents)
		{
			EventDispatcher::GetInstance().Dispatch(*onEnterEvent, GetParent());
		}

		if (auto it = m_OnEnterKeyEvents.find(otherGameObject); it != m_OnEnterKeyEvents.end())
		{
			for (auto& event : it->second)
			{
				EventDispatcher::GetInstance().Dispatch(*event, GetParent());
			}
		}
	}

	void WhileOutEvent(dae::GameObject* otherGameObject) const
	{
		for (auto& onEnterEvent : m_OnEnterEvents)
		{
			EventDispatcher::GetInstance().Dispatch(*onEnterEvent, GetParent());
		}

		if (auto it = m_OnEnterKeyEvents.find(otherGameObject); it != m_OnEnterKeyEvents.end())
		{
			for (auto& event : it->second)
			{
				EventDispatcher::GetInstance().Dispatch(*event, GetParent());
			}
		}
	}

	void Render() override{}

	virtual bool GetIsBlocking() const { return m_BlockOnCollision; }

	virtual glm::vec2 GetSize() const { return m_Size; }

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

	std::unordered_map<dae::GameObject*, std::vector<std::unique_ptr<Event>>> m_OnEnterKeyEvents{};
	std::unordered_map<dae::GameObject*, std::vector<std::unique_ptr<Event>>> m_OnExitKeyEvents{};
	std::unordered_map<dae::GameObject*, std::vector<std::unique_ptr<Event>>> m_WhileInKeyEvents{};
	std::unordered_map<dae::GameObject*, std::vector<std::unique_ptr<Event>>> m_WhileOutKeyEvents{};
};
#endif // COLLISIONCOMPONENT_H

#pragma once

#include <functional>
#include <typeindex>
#include <unordered_map>
#include <vector>
#include "Singleton.h"
#include "GameObject.h"  // Include the GameObject class

class Event
{
public:
    virtual ~Event() = default;
};

class EventDispatcher : public dae::Singleton<EventDispatcher>
{
    friend class Singleton;

public:
    using Callback = std::function<void(const Event&)>;

    // Register a callback with a game object for a specific event type
    template<typename EventType>
    void AddListener(dae::GameObject* gameObject, std::function<void(const EventType&)> listener)
    {
        auto wrapper = [listener](const Event& e)
            {
                listener(static_cast<const EventType&>(e));
            };

        // Store listeners mapped by event type and associated game object
        m_Listeners[typeid(EventType)].push_back({ gameObject, wrapper });
    }

    // Dispatch an event to all registered listeners
    void Dispatch(const Event& event,const dae::GameObject* gameObj) const
    {
        auto it = m_Listeners.find(typeid(event));
        if (it == m_Listeners.end()) return;

        for (const auto& [targetObj, callback] : it->second)
        {
            if ((targetObj == gameObj || targetObj == nullptr) && callback)
            {
                callback(event);
            }
        }
    }

    void RemoveListeners(dae::GameObject* gameObject)
    {
        for (auto& [eventType, listeners] : m_Listeners)
            std::erase_if(listeners,[gameObject](const ListenerEntry& entry)  
            {
	            return entry.gameObject == gameObject;
            });
        
    }

private:
    struct ListenerEntry
    {
	    dae::GameObject* gameObject;
        Callback callback;
    };

    std::unordered_map<std::type_index, std::vector<ListenerEntry>> m_Listeners;
};

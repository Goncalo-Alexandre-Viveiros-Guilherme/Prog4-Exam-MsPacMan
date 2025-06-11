#pragma once

#include <functional>
#include <typeindex>
#include <unordered_map>
#include <vector>
#include "Singleton.h"
#include "GameObject.h" 

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

    template<typename EventType>
    void AddListener(dae::GameObject* gameObject, std::function<void(const EventType&)> listener)
    {
        auto wrapper = [listener](const Event& e)
            {
                listener(static_cast<const EventType&>(e));
            };

        m_Listeners[typeid(EventType)].push_back({ gameObject, wrapper });
    }

    void Dispatch(const Event& event, const dae::GameObject* gameObj) const
    {
        auto it = m_Listeners.find(typeid(event));
        if (it == m_Listeners.end()) return;

        for (const auto& [targetObj, callback] : it->second)
        {
            if (targetObj == nullptr || targetObj == gameObj)
            {
                if (callback) callback(event);
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

#pragma once

#include <functional>
#include <typeindex>
#include "Events.h"
#include "Singleton.h"

// The central event dispatcher
class EventDispatcher: public dae::Singleton<EventDispatcher>
{
    friend class Singleton;

public:
    using Callback = std::function<void(const Event&)>;

    // Register a callback for a specific event type (identified by std::type_index)
    template<typename EventType>
    void AddListener(std::function<void(const EventType&)> listener) {
        auto wrapper = [listener](const Event& e) {
            listener(static_cast<const EventType&>(e));
            };
        m_Listeners[typeid(EventType)].push_back(wrapper);
    }

    // Dispatch an event to all registered listeners for its type
    void Dispatch(const Event& event) const {
        auto it = m_Listeners.find(typeid(event));
        if (it != m_Listeners.end()) {
            for (auto& callback : it->second) {
                callback(event);
            }
        }
    }

private:
    std::unordered_map<std::type_index, std::vector<Callback>> m_Listeners;
};
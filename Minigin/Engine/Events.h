#pragma once

class Event
{
public:
    virtual ~Event() = default;
};

// A specific event, e.g., health changed
class HealthChangedEvent : public Event {
public:
    HealthChangedEvent(float newHealth) : newHealth(newHealth) {}
    float newHealth;
};
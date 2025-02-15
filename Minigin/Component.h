#pragma once

namespace dae
{
	class GameObject;
}


class Component
{
public:
	explicit Component(const dae::GameObject* parent); 
    virtual ~Component() = default;
    Component(const Component& other) = delete;
    Component(Component&& other) = delete;
    Component& operator=(const Component& other) = delete;
    Component& operator=(Component&& other) = delete;

    void SetToDestroy();
    void SetIsEnabled(bool value);
    bool GetIsEnabled() const;
    bool GetIsMarkedForDestruction() const;

protected:
    const dae::GameObject* m_Parent; 
    bool m_IsEnabled;
    bool m_IsMarkedForDestruction{ false };
};



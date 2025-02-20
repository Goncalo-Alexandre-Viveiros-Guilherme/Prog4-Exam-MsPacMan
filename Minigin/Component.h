#pragma once

namespace dae
{
	class GameObject;
}


class Component
{
public:
	explicit Component(const dae::GameObject& parent); 
    virtual ~Component() = default;
    Component(const Component& other) = delete;
    Component(Component&& other) = delete;
    Component& operator=(const Component& other) = delete;
    Component& operator=(Component&& other) = delete;

    virtual void Update();
    virtual void Render();
	const dae::GameObject* GetParent() const;
    void SetToDestroy();
    void SetIsEnabled(bool value);
    bool GetIsEnabled() const;
    bool GetIsMarkedForDestruction() const;

protected:
    bool m_IsEnabled;
    bool m_IsMarkedForDestruction{ false };
private:
    const dae::GameObject* m_Parent;
};



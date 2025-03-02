#include "RotatorComponent.h"

#include "EngineTime.h"
#include "GameObject.h"
#include <numbers>

RotatorComponent::RotatorComponent(dae::GameObject& parent, float angle, float radius): Component(parent),
m_Radius(radius), m_AngleSpeed(angle), m_Angle(0)
{
	if (GetParent()->HasParent() == false) 
        m_CenterPos = GetParent()->GetLocalPosition();
}

void RotatorComponent::Update()
{
    static constexpr float twoPi = std::numbers::pi_v<float> *2;

    m_Angle += m_AngleSpeed * Time::GetInstance().GetDeltaTime();

    if (m_Angle > twoPi)
    {
        m_Angle -= twoPi;
    }

    const float x = m_CenterPos.x + m_Radius * cos(m_Angle );
    const float y = m_CenterPos.y + m_Radius * sin(m_Angle);
    GetParent()->SetLocalPosition(x, y);

}

void RotatorComponent::SetAngleSpeed(const float angleSpeed)
{
	m_AngleSpeed = angleSpeed;
}

void RotatorComponent::SetRadius(const float radius)
{
	m_Radius = radius;
}

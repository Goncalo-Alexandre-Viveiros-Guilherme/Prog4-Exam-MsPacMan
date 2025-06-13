#pragma once
#include "Component.h"

class FPSComponent final : public Component
{
public:
    FPSComponent(dae::GameObject* parent);
    void Update() override;
    float GetFps() const;

private:
    float m_Timer{0};
    const float m_Threshold{ 0.7f };
    int m_FrameCount{0};
    float m_ElapsedTime{0};
    float m_Fps;
};

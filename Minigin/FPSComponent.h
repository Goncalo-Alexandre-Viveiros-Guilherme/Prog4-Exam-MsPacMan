#pragma once
#include "Component.h"

class FPSComponent final : public Component
{
public:
    FPSComponent(const dae::GameObject* parent);
    void Update();
    float GetFps() const;

private:

    int m_frameCount{0};
    float m_elapsedTime{0};
    float m_fps;
};

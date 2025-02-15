#include "FPSComponent.h"

#include <chrono>

FPSComponent::FPSComponent(const dae::GameObject* parent): Component(parent), m_fps(0)
{
}


void FPSComponent::Update()
{
    using namespace std::chrono;
    static auto lastTime = high_resolution_clock::now();
    const auto currentTime = high_resolution_clock::now();
    const float deltaTime = duration<float>(currentTime - lastTime).count();
    lastTime = currentTime;

    m_elapsedTime += deltaTime;
    m_frameCount++;

    if (m_elapsedTime >= 1.0f)
    {
        m_fps = m_frameCount / m_elapsedTime;
        m_frameCount = 0;
        m_elapsedTime = 0.0f;
    }
}

float FPSComponent::GetFps() const
{
    return m_fps;
}



#include "EngineTime.h"

void Time::Update()
{
	const auto currentTime = std::chrono::high_resolution_clock::now();
	m_DeltaTime = std::chrono::duration<float>(currentTime - m_LastTime).count();
	m_LastTime = currentTime;
}

std::chrono::nanoseconds Time::SleepDuration() const
{
	return (m_LastTime + std::chrono::milliseconds(static_cast<int>(ms_per_frame)) - std::chrono::high_resolution_clock::now());
}

float Time::GetDeltaTime() const
{
	return m_DeltaTime;
}

float Time::GetFixedDeltaTime()
{
	return m_FixedTimeStep;
}

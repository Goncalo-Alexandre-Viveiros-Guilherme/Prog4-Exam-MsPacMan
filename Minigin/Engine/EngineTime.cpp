#include "EngineTime.h"

void Time::Update()
{
    m_CurrentTime = std::chrono::high_resolution_clock::now();
    m_DeltaTime = std::chrono::duration<float>(m_CurrentTime - m_LastTime).count();
    m_LastTime = m_CurrentTime;

	m_TotalTime += m_DeltaTime;
}

std::chrono::nanoseconds Time::SleepDuration() const
{
	return (m_CurrentTime + std::chrono::milliseconds(static_cast<int>(ms_per_frame)) - std::chrono::high_resolution_clock::now());
}

float Time::GetDeltaTime() const
{
	return m_DeltaTime;
}

float Time::GetTotalTime() const
{
	return m_TotalTime;
}

float Time::GetFixedDeltaTime()
{
	return m_FixedTimeStep;
}

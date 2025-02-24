#pragma once
#include "Singleton.h"
#include <chrono>

class Time : public dae::Singleton <Time>
{
	friend class Singleton;

public:

	void Update();
	std::chrono::nanoseconds SleepDuration() const;
	float GetDeltaTime() const;
	float GetTotalTime() const;
	static float GetFixedDeltaTime();

private:
	Time() = default;
	~Time() = default;
	Time(const Time& other) = delete;
	Time(Time&& other) = delete;
	Time& operator=(const Time& other) = delete;
	Time& operator=(Time&& other) = delete;	

	float m_DeltaTime{};
	float m_TotalTime{};
	std::chrono::high_resolution_clock::time_point m_CurrentTime{};
	static constexpr float m_FixedTimeStep{1 / 120.f};
	std::chrono::high_resolution_clock::time_point m_LastTime{ std::chrono::high_resolution_clock::now() };
	float m_SleepTime{};
	static constexpr double ms_per_frame{ 1000.f/120.f };
};

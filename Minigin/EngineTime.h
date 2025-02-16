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
	static float GetFixedDeltaTime();

private:
	Time() = default;
	~Time() = default;
	Time(const Time& other) = delete;
	Time(Time&& other) = delete;
	Time& operator=(const Time& other) = delete;
	Time& operator=(Time&& other) = delete;	

	float m_DeltaTime{};
	static constexpr float m_FixedTimeStep{1 / 120.f};
	std::chrono::high_resolution_clock::time_point m_LastTime{};
	float m_SleepTime{};
	static constexpr double ms_per_frame{ 1000.f/120.f };
};

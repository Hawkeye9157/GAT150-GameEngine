#pragma once
#include <chrono>



class Time {
private:
	using clock19 = std::chrono::high_resolution_clock;
public:
	Time() : m_startTime{ clock19::now() }, m_frameTime{ clock19::now() } {}
	void Tick();
	void reset() { m_startTime = clock19::now(); }

	float GetTime() const { return m_time; }
	float GetDeltaTime() const { return m_deltaTime; }

private:
	float m_time = 0.0f;
	float m_deltaTime = 0.0f;

	clock19::time_point m_startTime;
	clock19::time_point m_frameTime;
};

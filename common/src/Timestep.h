#ifndef TIME_STEP_H
#define TIME_STEP_H

#include <chrono>
#include <iostream>

class Timestep
{
public:
	Timestep() : m_Time(0) {}
	~Timestep() {}

	inline void Update()
	{
		m_Time = GetCurrentTimestamp();
	}

	inline void SetTime(std::time_t& time)
	{
		m_Time = time;
	}

	inline const std::time_t GetTime() const
	{
		return m_Time;
	}

	inline std::time_t GetCurrentTimestamp()
	{
		std::chrono::system_clock::time_point timePoint = std::chrono::system_clock::now();

		return std::chrono::system_clock::to_time_t(timePoint);
	}

private:
	std::time_t m_Time;
};

#endif // TIME_STEP_H
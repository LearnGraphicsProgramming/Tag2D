#ifndef FRAME_COUNTER_H
#define FRAME_COUNTER_H

#include <Timestep.h>
#include <chrono>
#include <Server.h>
#include <Logger.h>

class Server;

class FrameCounter
{
public:
	FrameCounter() : m_ShouldCount(false), m_FrameCounter(0), m_LastSavedTimestep(Timestep()), m_CurrentTimestep(Timestep()) {}
	~FrameCounter() {}

	void OnFrame()
	{
		if (!m_ShouldCount)
		{
			m_ShouldCount = true;
			m_LastSavedTimestep.Update();
		}

		if (m_ShouldCount)
		{
			m_FrameCounter++;

			m_CurrentTimestep.Update();

			
			if (m_CurrentTimestep.GetTime() - m_LastSavedTimestep.GetTime() == 1)
			{
				m_ShouldCount = false;
				log_info("Server FPS: %i", m_FrameCounter);
				m_FrameCounter = 0;
			}
		}

	}

private:
	bool m_ShouldCount;

	Timestep m_LastSavedTimestep;
	Timestep m_CurrentTimestep;

	uint32_t m_FrameCounter;
};

#endif // FRAME_COUNTER_H
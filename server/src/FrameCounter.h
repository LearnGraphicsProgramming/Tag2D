#ifndef FRAME_COUNTER_H
#define FRAME_COUNTER_H

#include "../../common/src/Timestep.h"
#include <chrono>
#include "Server.h"
#include "../../common/src/Logger.h"

class Server;

namespace Tag2D
{
	class FrameCounter
	{
	public:
		FrameCounter() : m_ShouldCount(false), m_FrameCounter(0), m_LastSavedTimestep(Timestep()), m_CurrentTimestep(Timestep()), m_ShowFrames(false) {}
		~FrameCounter() {}

		void SetConstantShowFrames(const bool show_frames)
		{
			m_ShowFrames = show_frames;
		}

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
					if (m_ShowFrames)
					{
						log_info("Server FPS: %i", m_FrameCounter);
					}
					m_FrameCounter = 0;
				}
			}

		}

	private:
		bool m_ShouldCount;
		bool m_ShowFrames;

		Timestep m_LastSavedTimestep;
		Timestep m_CurrentTimestep;

		uint32_t m_FrameCounter;
	};
}
#endif // FRAME_COUNTER_H

#include "Console.h"
#include <iostream>
#include "../../common/src/Logger.h"

namespace Tag2D
{
	Console::Console() : m_UserInput(UserInput()) {}

	Console::~Console() {}

	void Console::RegisterCommand(const std::string& command, CommandCallback callback)
	{
		m_Commands[command] = callback;
		log_info("[%i] New command added:!w %s", m_Commands.size(), command.c_str());
	}

	void Console::OnFrame()
	{
		if (m_UserInput.GetInput(m_Input))
		{
			const auto& pair = m_Commands.find(m_Input);
			
			if (pair == m_Commands.end())
			{
				log_info("Invalid command: %s", m_Input.c_str());
			}
			else
			{
				log_info("Command: %s", m_Input.c_str());
				pair->second();
			}
		}
	}
}

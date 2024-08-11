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

		// FIXME: Why do i need to use std::string::c_str to display std::string in console?
		log_info("[%i] New command added:!w %s", m_Commands.size(), command.c_str());
	}

	void Console::OnFrame()
	{
		std::string input;

		m_UserInput.CheckInput();

		if (m_UserInput.GetInput(input))
		{
			const auto& pair = m_Commands.find(input);
			
			if (pair == m_Commands.end())
			{
				log_info("Invalid command: %s", input.c_str());
			}
			else
			{
				log_info("Command: %s", input.c_str());
				pair->second();
			}
		}
	}
}

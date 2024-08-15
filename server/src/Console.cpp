#include "Console.h"
#include <iostream>
#include "../../common/src/Logger.h"

namespace Tag2D
{
	Console::Console()
		: m_Offset(0), m_Input{'\0'}
	{
	}

	Console::~Console()
	{
	}

	void Console::RegisterCommand(const std::string& command, CommandCallback callback)
	{
		m_Commands[command] = callback;

		// FIXME: Why do i need to use std::string::c_str to display std::string in console?
		log_info("[%i] New command added:!w %s", m_Commands.size(), command.c_str());
	}

	void Console::OnFrame()
	{
		if (_kbhit())
		{
			char key = getch();

			if (key != ENTER_KEY_CODE)
			{
				m_Input[m_Offset++] = key;
				m_Input[m_Offset + 1] = '\0';
			}
			else if (key == BACKSPACE_KEY_CODE)
			{
				if (m_Offset > 0)
				{
					m_Input[--m_Offset] = '\0';

					std::cout << "\033[A\033[2K";
					std::cout << m_Input;
				}
			}
			else
			{
				m_Input[m_Offset] = '\0';

				UserSentInput();

				memset(m_Input, '\0', sizeof(m_Input));
				m_Offset = 0;
			}
		}
	}
	void Console::UserSentInput()
	{
		const auto& command = m_Commands.find(std::string(m_Input));

		if (command == m_Commands.end())
		{
			log_info("Invalid command:!w %s", m_Input);
		}
		else
		{
			command->second();
		}
	}
}

#include "Console.h"
#include <iostream>

namespace Tag2D
{

	Console::Console()
	{
	}

	Console::~Console()
	{
	}

	void Console::RegisterCommand(const std::string& command, CommandCallback callback)
	{
		m_Commands[command] = callback;

		std::cout << "New command added: " << command << ". Total commands: " << m_Commands.size() << "\n";
	}

	void Console::OnFrame() const
	{
		std::cout << "Console OnFrame\n";
	}
}
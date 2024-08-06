#include "Console.h"
#include <iostream>

Console::Console()
{
}

Console::~Console()
{
}

void Console::RegisterCommand(char* command, CommandCallback callback)
{
	m_Commands.emplace_back(command, callback);

	std::cout << "New command added: " << command << ". Total commands: " << m_Commands.size() << "\n";
}
#ifndef CONSOLE_H
#define CONSOLE_H

#include <vector>
#include <utility>
#include <functional>


using CommandCallback = std::function<void>();
using Command = std::pair<char*, CommandCallback>;

class Console
{
public:
	Console();
	~Console();

	void RegisterCommand(char* command, CommandCallback callback);

private:
	std::vector<Command> m_Commands;
};

#endif // CONSOLE_H
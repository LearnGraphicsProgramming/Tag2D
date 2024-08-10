#ifndef CONSOLE_H
#define CONSOLE_H

#include <vector>
#include <functional>
#include <unordered_map>
#include <string>
#include <iostream>

#include "../../common/src/pc.h"
#include "UserInput.h"

namespace Tag2D
{
	// The console class it's responsible with reading user input, registering console commands and processing them.

	using CommandCallback = std::function<void()>;

	class Console
	{
	public:
		Console();
		~Console();

		void RegisterCommand(const std::string& command, CommandCallback callback);
		void OnFrame();

	private:
		UserInput m_UserInput;

		std::unordered_map<std::string, CommandCallback> m_Commands;
	};
}

#endif // CONSOLE_H

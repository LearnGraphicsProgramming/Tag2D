#ifndef CONSOLE_H
#define CONSOLE_H

#include "../../common/src/pc.h"
#include "UserInput.h"

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <functional>

namespace Tag2D
{

	// The console class it's responsible with reading user input, registering console commands and processing them.
	class Console
	{
		using CommandCallback = std::function<void()>;
	
	public:
		Console();
		~Console();

		void RegisterCommand(const std::string& command, CommandCallback callback);
		void OnFrame();

	private:
		UserInput m_UserInput;
		std::string m_Input;

		std::unordered_map<std::string, CommandCallback> m_Commands;
	};
}

#endif // CONSOLE_H

#ifndef CONSOLE_H
#define CONSOLE_H

#include <vector>
#include <functional>
#include <unordered_map>
#include <string>

namespace Tag2D
{
	// The console class it's responsible with registering console commands. It has a Bi-Directional relation with the Server class.

	using CommandCallback = std::function<void()>;

	class Console
	{
	public:
		Console();
		~Console();

		void RegisterCommand(const std::string& command, CommandCallback callback);
		void OnFrame() const;

	private:
		std::unordered_map<std::string, CommandCallback> m_Commands;
	};
}

#endif // CONSOLE_H
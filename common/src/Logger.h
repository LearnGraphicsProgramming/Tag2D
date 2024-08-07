#ifndef LOGGER_H
#define LOGGER_H

#include "pc.h"

#include <iostream>
#include <source_location>
#include <cstdarg>
#include <filesystem>
#include <unordered_map>

#define LOGGER_DEFAULT_COLOR "\033[0m"
#define LOGGER_MAX_BUFFER_LENGTH UINT8_MAX

#define FILE_NAME_HELPER(file) (strrchr(file, '\\') ? strrchr(file, '\\') + 1 : (strrchr(file, '/') ? strrchr(file, '/') + 1 : file))
#define FILE_NAME (FILE_NAME_HELPER(std::source_location::current().file_name()))
#define FUNCTION_NAME (std::source_location::current().function_name())
#define LINE (std::source_location::current().line())

namespace Tag2D
{
	extern const std::pair<std::string, std::string> COLOR_MAP[];

	struct LoggerOptions
	{
		std::string info_prefix;
		std::string warning_prefix;
		std::string error_prefix;
		bool show_time;
	};

	class Logger
	{
	public:
		Logger();
		~Logger();

		static Logger& Instance();

		void Init(std::shared_ptr<LoggerOptions> options);
		void info(const char* fmt...);
		void warning(const char* fmt...);
		void error(const char* fmt...);

	private:
		std::string AddColorToText(const char* buffer);

	private:
		static Logger m_Instance;
		std::shared_ptr<LoggerOptions> m_Options;
	};
}
#endif // LOGGER_H
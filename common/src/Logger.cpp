#include "Logger.h"

namespace Tag2D
{
    std::unordered_map<std::string, std::string> COLOR_MAP =
    {
        { "!w", "white" },
        { "!r", "red" },
        { "!y", "yellow" }
    };

    Logger::Logger() {}

    Logger::~Logger() {}

    Logger& Logger::Instance()
    {
        return m_Instance;
    }

    void Logger::Init(LoggerOptions& options)
    {

    }

    void Logger::info(const char* fmt ...)
    {

    }

    void Logger::warning( const char* fmt ...)
    {

    }

    void Logger::error(const char* fmt ...)
    {

    }

    std::string Logger::AddColorToText(const char* buffer)
    {
        char lastChar = '\0';
        std::string newString;

        // lexzor: The below code currently has an error
       
        //if (strlen(buffer) > LOGGER_MAX_BUFFER_LENGTH)
        //{
        //    std::cerr << "[CRITICAL INTERNAL ERROR: " << FUNCTION_NAME << "::" << LINE << "] Buffer length has exceeded the maximum value: " << LOGGER_MAX_BUFFER_LENGTH << "\n";
        //    return std::string(" -[ERROR]- ");
        //}

  
        for (uint8_t index = 0; index < strlen(buffer); index++)
        {
        }


        return std::string();
    }
}
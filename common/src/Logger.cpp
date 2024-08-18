#include "Logger.h"

/*
* Color table. FG -> foreground, BG -> background.
*
* Name            FG  BG
* Black           30  40
* Red             31  41
* Green           32  42
* Yellow          33  43
* Blue            34  44
* Magenta         35  45
* Cyan            36  46
* White           37  47
* Bright Black    90  100
* Bright Red      91  101
* Bright Green    92  102
* Bright Yellow   93  103
* Bright Blue     94  104
* Bright Magenta  95  105
* Bright Cyan     96  106
* Bright White    97  107
*/

namespace Tag2D
{
    Logger Logger::m_Instance;

    const std::pair<std::string, std::string> COLOR_MAP[] =
    {
        { "!d", LOGGER_DEFAULT_COLOR},
        { "!r", "\x1B[31m" },
        { "!g", "\x1B[32m" },
        { "!y", "\x1B[33m" },
        { "!w", "\x1B[97m" },
    };

    Logger::Logger() {}

    Logger::~Logger() {}

    Logger& Logger::Instance()
    {
        return m_Instance;
    }

    void Logger::Init(std::shared_ptr<LoggerOptions> options)
    {
        options->info_prefix = AddColorToText(options->info_prefix.c_str());
        options->warning_prefix = AddColorToText(options->warning_prefix.c_str());
        options->error_prefix = AddColorToText(options->error_prefix.c_str());

        m_Options = std::move(options);
    }

    void Logger::info(const std::source_location& source_location, const char* fmt ...)
    {
        char buffer[LOGGER_MAX_BUFFER_LENGTH];

        va_list args;
        va_start(args, fmt);
        std::vsnprintf(buffer, sizeof(buffer), fmt, args);
        va_end(args);

        std::cout << m_Options->info_prefix << AddColorToText(buffer) << LOGGER_DEFAULT_COLOR << "\n";
    }

    void Logger::warning(const std::source_location& source_location, const char* fmt ...)
    {
        char buffer[LOGGER_MAX_BUFFER_LENGTH];

        va_list args;
        va_start(args, fmt);
        std::vsnprintf(buffer, sizeof(buffer), fmt, args);
        va_end(args);

        std::cout << m_Options->warning_prefix << AddColorToText("!y(") << FILE_NAME(source_location) << "::" << LINE(source_location) << AddColorToText(")!w ") << AddColorToText(buffer) << LOGGER_DEFAULT_COLOR << "\n";
    }

    void Logger::error(const std::source_location& source_location, const char* fmt ...)
    {
        char buffer[LOGGER_MAX_BUFFER_LENGTH];

        va_list args;
        va_start(args, fmt);
        std::vsnprintf(buffer, sizeof(buffer), fmt, args);
        va_end(args);

        // FIXME: Create colors contants to be accessed directly from map so won't iterate everytime we need to use color in the Logger class.
        // FIXME: BUG: source_locations it's showing the data from Logger class.

        std::cerr << m_Options->error_prefix << AddColorToText("!r") << AddColorToText(buffer) << "\n";
        std::cerr << AddColorToText("!r- File:!w ") << FILE_NAME(source_location) << "\n";
        std::cerr << AddColorToText("!r- Function:!w ") << FUNCTION_NAME(source_location) << "\n";
        std::cerr << AddColorToText("!r- Line:!w ") << LINE(source_location) << LOGGER_DEFAULT_COLOR << "\n";
    }

    std::string Logger::AddColorToText(const char* buffer)
    {
        if (strlen(buffer) > LOGGER_MAX_BUFFER_LENGTH)
        {
            std::cerr << "[CRITICAL INTERNAL ERROR: "
                << FUNCTION_NAME(std::source_location::current())
                    << "::"
                    << LINE(std::source_location::current())
                << "] Logger::Buffer length has exceeded the maximum value: "
                << LOGGER_MAX_BUFFER_LENGTH
                << "\n";

            return std::string(" -[ERROR]- ");
        }

        std::string stringBuffer(buffer);
        size_t iPos = std::string::npos;

        int i = 0;

        for (const auto& [key, color] : COLOR_MAP)
        {
            while ((iPos = stringBuffer.find(key)) != std::string::npos)
            {
                stringBuffer.replace(iPos, key.size(), color);
            }
        }

        return stringBuffer;
    }
}
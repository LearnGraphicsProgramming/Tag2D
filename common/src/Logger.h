#ifndef LOGGER_H
#define LOGGER_H

#include "pc.h"
#include <iostream>

#include <source_location>

#ifdef DEBUG

#define FILE_NAME_HELPER(file) (strrchr(file, '\\') ? strrchr(file, '\\') + 1 : (strrchr(file, '/') ? strrchr(file, '/') + 1 : file))

#define FUNCTION_NAME (std::source_location::current().function_name())
#define LINE (std::source_location::current().line())
#define FILE_NAME (FILE_NAME_HELPER(std::source_location::current().file_name()))

#define log_critical(message) (std::cerr << "\n[CRITICAL] Error occured:\n- File: " << FILE_NAME << "\n- Line: " << LINE << "\n- Function: " << FUNCTION_NAME << ".\n- Error message: " << message << "\n\n")
#define log_info(message) (std::cout << "[" << FILE_NAME << "::" << LINE << "] " << message << "\n")

#endif // DEBUG

#endif // LOGGER_H
#ifndef USER_INPUT_H
#define USER_INPUT_H

#include "../../common/src/pc.h"
#include "../../common/src/Logger.h"

#ifdef WINDOWS
#include <conio.h>
#include <iostream>
#elif defined(LINUX) || defined(APPLE)
#include <ncurses.h>
#else
#error Unsupported platform
#endif

#define ENTER_KEY_CODE 13
#define BACKSPACE_KEY_CODE 8
#define MAX_USER_INPUT_SIZE UINT8_MAX

// FIXME: On Windows, the characters typed by the user are not showed in real time.

namespace Tag2D
{
	class UserInput
	{
	public:
		UserInput();
		~UserInput();

		void CheckInput();

	private:
		char m_Input[MAX_USER_INPUT_SIZE];
		uint8_t m_Offset;
	};
}

#endif // USER_INPUT_H

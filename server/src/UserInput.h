#ifndef USER_INPUT_H
#define USER_INPUT_H

#include "../../common/src/pc.h"
#include "../../common/src/Logger.h"


#include <iostream>

#if defined(LINUX) || defined(APPLE)
#include <stdio.h>
#include <sys/select.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>

#define STDIN 0
#define GetKeyboardChar getchar
#define ENTER_KEY_CODE 10
#endif

#if defined(WINDOWS)
#include <conio.h>

#define GetKeyboardChar getch
#define ENTER_KEY_CODE 13
#endif

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
		bool GetInput(std::string& buffer);

	private:
		const bool KeyboardHit() const;

	private:
		char m_Input[MAX_USER_INPUT_SIZE];
		uint8_t m_Offset;

		bool m_PressedEnter;

#if defined(MACOS) || defined(LINUX)
		termios m_Termios;
#endif
	};
}

#endif // USER_INPUT_H

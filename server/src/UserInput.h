#ifndef USER_INPUT_H
#define USER_INPUT_H

#include "../../common/src/pc.h"
#include "../../common/src/Logger.h"

#if defined(WINDOWS)
#include <conio.h>
#include <iostream>

#define ENTER_KEY_CODE 13
#define BACKSPACE_KEY_CODE 8

#elif defined(LINUX) || defined(APPLE)
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <sys/select.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define STDIN 0
#define ENTER_KEY_CODE '\n'
#define BACKSPACE_KEY_CODE '\b'

#else
#error Unsupported platform
#endif

#define MAX_USER_INPUT_SIZE UINT8_MAX

namespace Tag2D
{

#if defined(LINUX)
	inline int _kbhit()
	{
		static bool initialized = false;

		if (!initialized) {
			termios term{};
			tcgetattr(STDIN, &term);
			term.c_lflag &= ~ICANON;
			tcsetattr(STDIN, TCSANOW, &term);
			setbuf(stdin, NULL);
			initialized = true;
		}

		int bytesWaiting;
		ioctl(STDIN, FIONREAD, &bytesWaiting);
		return bytesWaiting;
	}

	inline char getch(void)
	{
		char buf = 0;
		termios term{};
		fflush(stdout);

		if(tcgetattr(0, &term) < 0)
		{
			perror("tcsetattr()");
		}

		term.c_lflag &= ~(ICANON | ECHO);
		term.c_cc[VMIN] = 1;
		term.c_cc[VTIME] = 0;

		if(tcsetattr(0, TCSANOW, &term) < 0)
		{
			perror("tcsetattr ICANON");
		}

		if(read(0, &buf, 1) < 0)
		{
			perror("read()");
		}

		term.c_lflag |= ICANON;
		term.c_lflag |= ECHO;
		if(tcsetattr(0, TCSADRAIN, &term) < 0)
		{
			perror("tcsetattr ~ICANON");
		}

		return buf;
	}
#endif

	// FIXME: On Windows, the characters typed by the user are not showed in real time.

	class UserInput
	{
	public:
		UserInput();
		~UserInput();

		void CheckInput();
		bool GetInput(std::string& buffer);

	private:
		char m_Input[MAX_USER_INPUT_SIZE];
		uint8_t m_Offset;

		bool m_PressedEnter;
	};
}

#endif // USER_INPUT_H
#include "UserInput.h"

namespace Tag2D
{
	UserInput::UserInput() 
		: m_Input{0}, m_Offset(0), m_PressedEnter(false)
	{}

	UserInput::~UserInput() {}

	void UserInput::CheckInput()
	{
#ifdef WINDOWS
		if (_kbhit())
		{
			char key = getch();

			if (key == ENTER_KEY_CODE)
			{
				if (m_Offset > 0)
				{
					m_Input[m_Offset] = '\0';
					m_PressedEnter = true;
				}
			}
			else if (key == BACKSPACE_KEY_CODE)
			{
				if (m_Offset > 0)
				{
					m_Input[--m_Offset] = '\0';
					std::cout << m_Input;
				}
			}
			else 
			{
				m_Input[m_Offset++] = key;
				m_Input[m_Offset + 1] = '\0';
			}
		}
#elif defined(MACOS) || defined (LINUX)
		termios term;
		char pressedChar = 0;

		tcgetattr(STDIN, &term);
		term.c_lflag &= ~ICANON; 
		term.c_lflag &= ~ECHO;
		tcsetattr(STDIN, TCSANOW, &term);
		setbuf(stdin, NULL);

		int bytesWaiting;
		do {
			ioctl(STDIN, FIONREAD, &bytesWaiting); 
			if (bytesWaiting > 0) {
				pressedChar = getchar();
			}
		} while (bytesWaiting == 0);

		std::cout << "You pressed: " << pressedChar;
#endif
	}
	bool UserInput::GetInput(std::string& buffer)
	{
		if (m_PressedEnter)
		{
			buffer = std::string(m_Input);
			memset(m_Input, '\0', sizeof(m_Input));
			m_Offset = 0;
			m_PressedEnter = false;

			return true;
		}

		return false;
	}
}

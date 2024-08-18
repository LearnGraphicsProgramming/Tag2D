#include "UserInput.h"

namespace Tag2D
{
	UserInput::UserInput() 
		: m_Input{0}, m_Offset(0), m_PressedEnter(false)
	{
#if defined(MACOS) || defined(LINUX)
		tcgetattr(STDIN, &m_Termios);
		m_Termios.c_lflag &= ~ICANON;
		m_Termios.c_lflag &= ~ECHO;
		tcsetattr(STDIN, TCSANOW, &m_Termios);
		setbuf(stdin, NULL);
#endif
	}

	UserInput::~UserInput() {}

	void UserInput::CheckInput()
	{
		if (KeyboardHit())
		{
			char key = GetKeyboardChar();

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

	const bool UserInput::KeyboardHit() const
	{
#if defined(MACOS) || defined(LINUX)
		static int writeBytes = 0;
		ioctl(STDIN, FIONREAD, &writeBytes);

		return writeBytes > 0;
#else
		return _kbhit() != 0;
#endif
	}
}

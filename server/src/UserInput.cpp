#include "UserInput.h"

namespace Tag2D
{
	UserInput::UserInput() 
		: m_Input{0}, m_Offset(0), m_PressedEnter(false)
	{}

	UserInput::~UserInput() {}

	void UserInput::CheckInput()
	{
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

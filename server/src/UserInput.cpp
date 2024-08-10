#include "UserInput.h"

namespace Tag2D
{
	UserInput::UserInput() 
		: m_Input{ 0 }, m_Offset(0) {}

	UserInput::~UserInput() {}

	void UserInput::CheckInput()
	{
#ifdef WINDOWS
		// _keyboardhit?
		if (_kbhit())
		{
			// yes? ok, get characted (the ASCII code for characters are between 0-255 values (sizeof(short)). It will be returned as an int value (ASCII CODE), but it's ok to save it in a char type variable.
			char key = getch();

			// Did the user hit Enter button?
			if (key == ENTER_KEY_CODE)
			{
				// Ok, set the last offset of the saved input as a null byte so we can print it below
				m_Input[m_Offset] = '\0';

				log_info("User pressed enter. Input: %s", m_Input);

				// Reset the input and offset: we took the input and sent it to the console
				memset(m_Input, '\0', sizeof(m_Input));
				m_Offset = 0;

				// Call the event which should announce the console there is an input to be processed
				// SomeFunctionToSendTheInputToTheConsole(m_Input)
			}
			// Did the user just deleted a characted from the input?
			else if (key == BACKSPACE_KEY_CODE)
			{
				// Ok, this will come later, ignore code from this statement, i just tried to do an workaround, but there is actually more to do (like saving the input handler, printing whitespace characters to override the actual written input..) etc.... This will come later.
				if (m_Offset > 0)
				{
					m_Input[--m_Offset] = '\0';
					std::cout << m_Input;
				}
			}
			else // Did the user pressed a key that it is not enter or backspace?
			{
				// Ok, set the input string byte as the key value
				m_Input[m_Offset++] = key;
				m_Input[m_Offset + 1] = '\0';
			}
		}
#elif defined(MACOS) || defined (LINUX)
		// code for MacOS/Linux
#endif
	}
}

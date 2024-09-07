#ifndef INPUT_H
#define INPUT_H

#include <Window.h>
#include <unordered_map>

namespace Tag2D
{
	class Input
	{
	public:
		Input();
		~Input();
		static Input& Instance();

		void ProcessInput(GLFWwindow* window);

		bool KeyPress(int key_code);

	private:
		static Input m_Instance;
	
		std::unordered_map<int, bool> m_PressedKeys;
	};
}

#endif // INPUT_H
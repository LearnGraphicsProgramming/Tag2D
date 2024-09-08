#include "Input.h"
#include "Logger.h"

namespace Tag2D
{
    Input Input::m_Instance;

    Input::Input() {}
    Input::~Input() {}

    Input& Input::Instance()
    {
        return m_Instance;
    }

    void Input::ProcessInput(GLFWwindow* window)
    {
        m_PressedKeys[GLFW_KEY_W] = glfwGetKey(window, GLFW_KEY_W);
        m_PressedKeys[GLFW_KEY_A] = glfwGetKey(window, GLFW_KEY_A);
        m_PressedKeys[GLFW_KEY_S] = glfwGetKey(window, GLFW_KEY_S);
        m_PressedKeys[GLFW_KEY_D] = glfwGetKey(window, GLFW_KEY_D);
        m_PressedKeys[GLFW_KEY_Z] = glfwGetKey(window, GLFW_KEY_Z);
        m_PressedKeys[GLFW_KEY_X] = glfwGetKey(window, GLFW_KEY_X);
    }

    bool Input::KeyPress(int key_code)
    {
        if (m_PressedKeys.find(key_code) == m_PressedKeys.end())
        {
            log_warning("Key code !y%i!d (alias !y%c!d) has not been registered", key_code, static_cast<char>(key_code));
            return false;
        }

        return m_PressedKeys[key_code];
    }
}

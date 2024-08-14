#include "Window.h"
#include "Globals.h"

namespace Tag2D
{
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		log_error("GLFW Error (%i) : %s", error, description);
	}

	Window::Window(const WindowProperties& properties)
		: m_Shaders(Shaders())
	{
		m_Data.Title = properties.Title;
		m_Data.IconPath = properties.IconPath;
		m_Data.Width = properties.Width;
		m_Data.Height = properties.Height;

		log_info("Creating window \"%s\" (%i, %i)", m_Data.Title.c_str(), m_Data.Width, m_Data.Height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			if (!success)
				log_error("Could not intialize GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFWInitialized = true;
		}


		log_info("Loading OpenGL 3.3 core");
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef APPLE
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

		// TODO: CMDR-JohnAlex: Add the ability to load as different window modes. (Windowed, Fullscreen, Borderless)
		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);

		glfwMakeContextCurrent(m_Window);
		LoadIcon(m_Data.IconPath);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (!status)
		{
			log_error("Failed to initialize glad!");
		}

		try {

			m_Shaders.InitShaders();
		}
		catch (std::exception& e) {
			log_error("Initializing of one of the shader failed. Closing application..");
			glfwTerminate();

			return;
		}
		
		glfwSetWindowUserPointer(m_Window, &m_Data);
		glfwSetFramebufferSizeCallback(m_Window, FramebufferSizeCallback);
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	void Window::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);

		float time = static_cast<float>(glfwGetTime());
		float deltatime = time - m_LastFrameTime;
		m_LastFrameTime = time;
	}

	void Window::SetVSync(bool enabled)
	{
		m_Data.VSync = enabled;
		glfwSwapInterval(enabled);
	}

	void Window::SetTitle(const std::string& title)
	{
		m_Data.Title = title;
		glfwSetWindowTitle(m_Window, m_Data.Title.c_str());
	}

	void Window::SetIconPath(const std::string& iconPath)
	{
		m_Data.IconPath = iconPath;
		LoadIcon(m_Data.IconPath);
	}

	std::pair<float, float> Window::GetWindowPosition() const
	{
		int width, height;
		glfwGetWindowPos(m_Window, &width, &height);
		return { width, height };
	}

	void Window::Start()
	{
		log_info("!wStarting game loop..");

		TriggerEventCallback(WindowEventType::Start);

		while (!ShouldClose())
		{
			glClearColor(1.0f, 0.0f, 0.54901960784f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			TriggerEventCallback(WindowEventType::Update);

			glfwPollEvents();
			glfwSwapBuffers(m_Window);
		}

		TriggerEventCallback(WindowEventType::Close);

		// TODO: Must free m_ShaderProgram from Shaders
		glfwTerminate();
	}

	void Window::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void Window::RegisterWindowCallback(const WindowEventType& type, EventCallbackFn function)
	{
		m_EventsCallbacks[type].push_back(function);
	}

	void Window::UnregisterWindowCallback(std::unordered_map<WindowEventType, int>& class_callback_ids)
	{
		for (const auto& [eventType, registeredCallbackID] : class_callback_ids)
		{
			auto it = m_EventsCallbacks.find(eventType);

			if (it != m_EventsCallbacks.end())
			{
				std::vector<EventCallbackFn>& callbacksVector = it->second;
				if (registeredCallbackID < callbacksVector.size())
				{
					callbacksVector.erase(callbacksVector.begin() + registeredCallbackID);
				}
			}
		}
	}

	void Window::TriggerEventCallback(const WindowEventType& type) const
	{
		auto it = m_EventsCallbacks.find(type);

		if (it != m_EventsCallbacks.end())
		{
			const std::vector<EventCallbackFn>& callbacksVector = it->second;

			for (const auto& callbackFunction : callbacksVector)
			{
				callbackFunction();
			}
		}
	}

	void Window::LoadIcon(const std::string& iconPath)
	{
		// TODO: CMDR-JohnAlex: Add stb_image.h to load icons.
		log_warning("Window::LoadIcon() needs to be implemented!");
	}
}
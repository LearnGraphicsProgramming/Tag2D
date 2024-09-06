#include "Application.h"
#include "Logger.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/VertexBuffer.h"

namespace Tag2D
{
	Application Application::m_Instance;
	Application::Application() {}
	Application::~Application() {}

	Application& Application::Instance()
	{
		return m_Instance;
	}

	void Application::Init()
	{
		{
			WindowProperties properties = { "Tag2D Client", "assets/icon/tag2d_icon.png", 1280, 720 };
			m_Window = std::make_shared<Tag2D::Window>(properties);
		}
		
		m_Window->SetVSync(true);
		m_ActiveScene = std::make_unique<Scene>();
		m_ActiveScene->Init();
	}

	void Application::Run()
	{

		while (!m_Window->ShouldClose())
		{
			m_Window->OnUpdate();
			m_ActiveScene->OnUpdate();
			m_Window->OnUpdatePost();
		}

		glfwTerminate();
	}
}
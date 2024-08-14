#include "Application.h"

namespace Tag2D
{
	Application::Application()
	{
		m_Entities.resize(CLIENT_MAX_ENTITIES);
	}

	Application::~Application()
	{
		m_Entities.clear();
	}

	void Application::Init()
	{
		{
			Tag2D::WindowProperties properties = { "Tag2D Client", "", 1280, 720 };
			m_Window = std::make_shared<Tag2D::Window>(properties);
		}

		m_Window->SetVSync(true);
	}
	void Application::Run()
	{
		m_Window->Start();
	}
}
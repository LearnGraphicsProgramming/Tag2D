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
	}

	void Application::Run()
	{
		TriggerEventCallback(ApplicationEventType::Start); 

		float positions[] = {
			 0.5f,  0.5f, 0.0f,  // Top-right corner of the first triangle
			 0.9f,  0.0f, 0.0f,  // Middle-right edge
			 0.5f, -0.5f, 0.0f,  // Bottom-right corner
		};

		float positions2[] = {
			-0.5f,  0.5f, 0.0f,  // Top-left corner of the second triangle
			-0.9f,  0.0f, 0.0f,  // Middle-left edge
			-0.5f, -0.5f, 0.0f,  // Bottom-left corner
		};

		unsigned int vao[2]{ 0 };
		unsigned int vbo[2]{ 0 };

		// First Triangle
		//glGenVertexArrays(1, &vao[0]);
		//glBindVertexArray(vao[0]);

		//glGenBuffers(1, &vbo[0]);
		//glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		//glEnableVertexAttribArray(0);

		// Second Triangle
		//glGenVertexArrays(1, &vao[1]);
		//glBindVertexArray(vao[1]);

		//glGenBuffers(1, &vbo[1]);
		//glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(positions2), positions2, GL_STATIC_DRAW);

		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		//glEnableVertexAttribArray(0);

		VertexArray va1;
		VertexBuffer vb1;
		vb1.Bind();
		vb1.AssignVertices(positions, sizeof(positions));
		va1.AssingData(vb1);

		VertexArray va2;
		VertexBuffer vb2;
		vb2.Bind();
		vb2.AssignVertices(positions2, sizeof(positions2));
		va2.AssingData(vb2);


		while (!m_Window->ShouldClose())
		{
			m_Window->OnUpdate();

			va1.Draw();
			va2.Draw();

			m_Window->OnUpdatePost();
		}

		TriggerEventCallback(ApplicationEventType::Close);
		glfwTerminate();
	}

	uint8_t Application::RegisterApplicationCallback(const ApplicationEventType& type, EventCallbackFn function)
	{
		m_EventsCallbacks[type].emplace_back(function);
		return m_EventsCallbacks[type].size() - 1;
	}

	void Application::UnregisterApplicationCallback(std::unordered_map<ApplicationEventType, int>& class_callback_ids)
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
					break;
				}
			}
		}
	}

	void Application::TriggerEventCallback(const ApplicationEventType& type) const
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
}
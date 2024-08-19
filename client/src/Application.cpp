#include "Application.h"
#include "Logger.h"

namespace Tag2D
{
	Application Application::m_Instance;

	Application::Application()
	{
		//m_Entities.resize(CLIENT_MAX_ENTITIES);
	}

	Application::~Application()
	{
		//m_Entities.clear();
	}

	Application& Application::Instance()
	{
		return m_Instance;
	}

	void Application::Init()
	{
		{
			Tag2D::WindowProperties properties = { "Tag2D Client", "assets/icon/tag2d_icon.png", 1280, 720 };
			m_Window = std::make_shared<Tag2D::Window>(properties);
		}

		m_Window->SetVSync(true);

		std::shared_ptr<Cube> cube = std::make_shared<Cube>();
		m_Entities.push_back(std::move(cube));
	}

	void Application::Run()
	{
		TriggerEventCallback(ApplicationEventType::Start); 
		
		while (!m_Window->ShouldClose())
		{
			m_Window->OnUpdate();
			TriggerEventCallback(ApplicationEventType::Update);
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
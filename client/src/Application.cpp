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
			Tag2D::WindowProperties properties = { "Tag2D Client", "", 1280, 720 };
			m_Window = std::make_shared<Tag2D::Window>(properties);
		}

		m_Window->SetVSync(true);

		std::shared_ptr<Entity> entity1 = std::make_shared<Entity>();
		entity1->m_Vertices = std::vector<float>({
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
			});
		entity1->SetEntityClassName("triangle_1");

		m_Entities.emplace_back(std::move(entity1));

		std::shared_ptr<Entity> entity2 = std::make_shared<Entity>();
		entity2->m_Vertices = std::vector<float>({
			0.5f, 0.5f, 1.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
			});

		entity2->SetEntityClassName("triangle_2");

		m_Entities.push_back(std::move(entity2));
	}

	void Application::Run()
	{
		TriggerEventCallback(ApplicationEventType::Start); 
		
		while (!m_Window->ShouldClose())
		{
			TriggerEventCallback(ApplicationEventType::Update);
			m_Window->OnUpdate();
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
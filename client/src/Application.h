#ifndef APPLICATION_H
#define APPLICATION_H

#include "ApplicationEvents.h"
#include "Window.h"
#include "Entities/BaseEntity.h"
#include "Entities/Entity.h"

#include <memory>
#include <vector>
#include <functional>

namespace Tag2D
{
	class BaseEntity;

	class Application
	{
		using EventCallbackFn = std::function<void()>;
	public:
		Application();
		~Application();
		static Application& Instance();

		void Init();
		void Run();

		uint8_t RegisterApplicationCallback(const ApplicationEventType& type, EventCallbackFn function);
		void UnregisterApplicationCallback(std::unordered_map<ApplicationEventType, int>& class_callback_ids);
		void TriggerEventCallback(const ApplicationEventType& type) const;

	private:
		static Application m_Instance;

		std::shared_ptr<Window> m_Window;

		std::vector<std::shared_ptr<BaseEntity>> m_Entities;
		
		std::unordered_map<
			ApplicationEventType,
			std::vector<EventCallbackFn>
		> m_EventsCallbacks;
	};
}

#endif // APPLICATION_H
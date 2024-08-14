#ifndef BASE_ENTITY_H
#define BASE_ENTITY_H

#include "Window.h"

#include <memory>
#include <unordered_map>

namespace Tag2D
{
	class BaseEntity
	{
	public:
		virtual inline ~BaseEntity()
		{
			m_ParentWindow->UnregisterWindowCallback(m_CallbackIDs);
		}

	protected:
		inline BaseEntity(std::shared_ptr<Window> window) : m_ParentWindow(window)
		{
			m_ParentWindow->RegisterWindowCallback(WindowEventType::Start, [this]() { OnStart(); });
			m_ParentWindow->RegisterWindowCallback(WindowEventType::Update, [this]() { OnUpdate(); });
			m_ParentWindow->RegisterWindowCallback(WindowEventType::Close, [this]() { OnClose(); });
		}
		
		virtual void OnStart() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnClose() = 0;

	private:
		const std::shared_ptr<Window> m_ParentWindow = nullptr;
		int m_OnStartCallbackID = 0;
		int m_OnUpdateCallbackID = 0;
		int m_OnCloseCallbackID = 0;

		std::unordered_map<WindowEventType, int> m_CallbackIDs;
	};
}

#endif // BASE_ENTITY_H
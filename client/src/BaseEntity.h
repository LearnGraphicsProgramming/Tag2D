#ifndef BASE_ENTITY_H
#define BASE_ENTITY_H

#include "ApplicationEvents.h"

#include <memory>
#include <unordered_map>
#include <string>

namespace Tag2D
{
	class Application;

	class BaseEntity
	{
	public:
		virtual ~BaseEntity();

		void SetEntityClassName(const std::string& name);
		void ToString() const;

	protected:
		BaseEntity();
		
		virtual void OnStart() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnClose() = 0;

	protected:
		std::string m_EntityName;

	private:
		uint8_t m_OnStartCallbackID;
		uint8_t m_OnUpdateCallbackID;
		uint8_t m_OnCloseCallbackID;

		std::unordered_map<ApplicationEventType, int> m_CallbackIDs;
	};
}

#endif // BASE_ENTITY_H
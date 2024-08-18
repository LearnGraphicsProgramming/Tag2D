#include "BaseEntity.h"
#include "Application.h"
#include "Logger.h"

namespace Tag2D
{
	BaseEntity::BaseEntity()
		: m_OnStartCallbackID(0), m_OnUpdateCallbackID(0), m_OnCloseCallbackID(0)
	{
		m_OnStartCallbackID = Application::Instance().RegisterApplicationCallback(ApplicationEventType::Start, [this]() { OnStart(); });
		m_OnUpdateCallbackID = Application::Instance().RegisterApplicationCallback(ApplicationEventType::Update, [this]() { OnUpdate(); });
		m_OnCloseCallbackID = Application::Instance().RegisterApplicationCallback(ApplicationEventType::Close, [this]() { OnClose(); });
	}

	BaseEntity::~BaseEntity()
	{
		Application::Instance().UnregisterApplicationCallback(m_CallbackIDs);
	}

	void BaseEntity::SetEntityClassName(const std::string& name)
	{
		m_EntityName = name.data();
	}

	void BaseEntity::ToString() const
	{
		log_info("!r-!w Entity name:!d'%s'", m_EntityName.size() > 0 ? m_EntityName.c_str() : "NAME_NOT_SET");
		log_info("!r-!w OnStartCallbackID:!d %i", m_OnStartCallbackID);
		log_info("!r-!w OnUpdateCallbackID:!d %i", m_OnUpdateCallbackID);
		log_info("!r-!w OnCloseCallbackID:!d %i", m_OnCloseCallbackID);
	}
}

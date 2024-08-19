#include "BaseEntity.h"
#include "Application.h"
#include "Logger.h"

namespace Tag2D
{
	BaseEntity::BaseEntity()
		: m_OnStartCallbackID(0), m_OnUpdateCallbackID(0), m_OnCloseCallbackID(0),
		m_VertexArrayObject(0), m_VertexBufferObject(0), m_EntityHasNoVerticesMessageSent(false),
		m_VerticesNum(0)
	{
		m_OnStartCallbackID = Application::Instance().RegisterApplicationCallback(ApplicationEventType::Start, [this]() { OnStart(); });

		m_OnUpdateCallbackID = Application::Instance().RegisterApplicationCallback(ApplicationEventType::Update, [this]() {
			OnUpdate_Internal();
			OnUpdate();
		});

		m_OnCloseCallbackID = Application::Instance().RegisterApplicationCallback(ApplicationEventType::Close, [this]() { OnClose(); });

		SetEntityClassName("player_cube");
	}

	BaseEntity::~BaseEntity()
	{
		Application::Instance().UnregisterApplicationCallback(m_CallbackIDs);
	}

	void BaseEntity::BindOpenGLBuffer()
	{
		glGenBuffers(1, &m_VertexBufferObject);

		glGenVertexArrays(1, &m_VertexArrayObject);
		glBindVertexArray(m_VertexArrayObject);

		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, m_VerticesNum * 3 * sizeof(float), m_Vertices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(
			0, // index of the vertex attribute
			3, // number of components per vertex attribute (x, y, z)
			GL_FLOAT, // data type of each component
			GL_FALSE, // whether the data should be normalized
			3 * sizeof(float), // stride (distance between consecutive vertex attributes)
			(void*)0 // offset where the position data begins in the buffer
		);

		glEnableVertexAttribArray(0);
	}

	void BaseEntity::OnUpdate_Internal()
	{
		if (m_VerticesNum == 0)
		{
			if (!m_EntityHasNoVerticesMessageSent)
			{
				log_warning("Entity!cb %s!d has been created, but has no vertices.", m_EntityName.c_str());

				m_EntityHasNoVerticesMessageSent = true;

				return;
			}
		}

		glBindVertexArray(m_VertexArrayObject);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, m_VerticesNum);
	}

	void BaseEntity::SetEntityClassName(const std::string& name)
	{
		m_EntityName = name.data();
	}

	void BaseEntity::SetVertices(const std::initializer_list<float>& initializer_list)
	{

		for (const float& vertice : initializer_list)
		{
			m_Vertices.emplace_back(vertice);
		}

		m_VerticesNum = m_Vertices.size() / 3;

		BindOpenGLBuffer();
	}

	void BaseEntity::ToString() const
	{
		log_info("!r-!w Entity name:!d'%s'", m_EntityName.size() > 0 ? m_EntityName.c_str() : "NAME_NOT_SET");
		log_info("!r-!w OnStartCallbackID:!d %i", m_OnStartCallbackID);
		log_info("!r-!w OnUpdateCallbackID:!d %i", m_OnUpdateCallbackID);
		log_info("!r-!w OnCloseCallbackID:!d %i", m_OnCloseCallbackID);
	}
}
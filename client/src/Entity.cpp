#include "Entity.h"
#include "Logger.h"

namespace Tag2D
{
	Entity::Entity(std::shared_ptr<Window> window) : BaseEntity(window), m_VertexArrayObject(0), m_VertexBufferObject(0) {}

	Entity::~Entity() {}

	void Entity::OnStart()
	{
		glGenBuffers(1, &m_VertexBufferObject);

		glGenVertexArrays(1, &m_VertexArrayObject);
		glBindVertexArray(m_VertexArrayObject);

		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(float), m_Vertices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		glEnableVertexAttribArray(0);
	}

	void Entity::OnUpdate()
	{
		glBindVertexArray(m_VertexBufferObject);
		glDrawArrays(GL_TRIANGLES, 0, m_Vertices.size() / 3);
	}

	void Entity::OnClose()
	{
		log_info("Entity::OnClose");
	}
}

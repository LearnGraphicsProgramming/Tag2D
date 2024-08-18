#include "Entity.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "Logger.h"

namespace Tag2D
{
	Entity::Entity()
		: m_VertexArrayObject(0), m_VertexBufferObject(0) {}

	Entity::~Entity() {}

	void Entity::OnStart()
	{
		if (m_Vertices.size() == 0)
		{
			log_error("Entity does not have vertices.");
			return;
		}

		glGenBuffers(1, &m_VertexBufferObject);

		glGenVertexArrays(1, &m_VertexArrayObject);
		glBindVertexArray(m_VertexArrayObject);

		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(float), m_Vertices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

		glEnableVertexAttribArray(0);

		log_info("Entity !w'%s'!d initialized. Vertices[0]: %f", m_EntityName.c_str(), m_Vertices[0]);
	}

	void Entity::OnUpdate()
	{
		glBindVertexArray(m_VertexArrayObject);
		glDrawArrays(GL_TRIANGLES, 0, m_Vertices.size() / 3);
	}

	void Entity::OnClose()
	{
		log_info("Entity::OnClose");
	}
}
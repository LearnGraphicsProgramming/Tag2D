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

		log_info("Entity !bc%s!d initialized", m_EntityName.c_str());
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
	void Entity::SetVertices(const std::initializer_list<float>& initializer_list)
	{
		for (const float& vertice : initializer_list)
		{
			m_Vertices.emplace_back(vertice);
		}
	}
}

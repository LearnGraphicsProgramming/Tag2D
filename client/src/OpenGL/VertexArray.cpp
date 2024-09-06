#include "VertexArray.h"

namespace Tag2D
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);
		glBindVertexArray(m_RendererID);
	}

	VertexArray::~VertexArray()
	{
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void VertexArray::Unbind() const
	{
	}

	void VertexArray::Draw() const
	{
		Bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	void VertexArray::AssingData(const VertexBuffer& vertex_buffer)
	{
		m_Data.push_back(vertex_buffer);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
	}
}

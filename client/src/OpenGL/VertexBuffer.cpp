#include "VertexBuffer.h"
#include "Logger.h"


namespace Tag2D
{
	VertexBuffer::VertexBuffer()
		: m_RendererID(0)
	{}

	VertexBuffer::~VertexBuffer()
	{}

	void VertexBuffer::AssignVertices(const float* data, unsigned int size)
	{
		glGenBuffers(1, &m_RendererID);
		Bind();
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
	
	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void VertexBuffer::Unbind() const
	{
		glBindBuffer(0, m_RendererID);
	}
}
#include "Triangle.h"
#include "Logger.h"

namespace Tag2D
{
	Triangle::Triangle()
		: m_EntityID(0) {}

	Triangle::~Triangle() {}

	void Triangle::AssignVertices(const void* data, unsigned int size)
	{
		log_info("Initializing !w'Triangle'!d entity")
		m_VertexArray.Init();

		m_VertexBuffer.Init();
		m_VertexBuffer.Bind();
		m_VertexBuffer.AssignVertices(data, size);

		m_VertexArray.AssingData(m_VertexBuffer);
	}

	void Triangle::Draw() const
	{
		m_VertexArray.Draw();
	}

	void Triangle::SetID(unsigned int index)
	{
		m_EntityID = index;
	}

	unsigned int Triangle::GetID() const
	{
		return m_EntityID;
	}
}
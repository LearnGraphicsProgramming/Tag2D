#pragma once
#include "OpenGL/VertexArray.h"
#include "OpenGL/VertexBuffer.h"

namespace Tag2D
{
	class Triangle
	{
	public:
		Triangle();
		~Triangle();
		void AssignVertices(const void* data, unsigned int size);
		void Draw() const;

		void SetID(unsigned int index);
		unsigned int GetID() const;

	private:
		unsigned int m_EntityID;
		VertexArray m_VertexArray;
		VertexBuffer m_VertexBuffer;
	};
}
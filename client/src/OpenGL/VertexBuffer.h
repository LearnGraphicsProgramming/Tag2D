#pragma once

#include <glad/glad.h>

#include <vector>

namespace Tag2D
{
	class VertexBuffer
	{
	public:
		VertexBuffer();
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;
		void AssignVertices(const float* data, unsigned int size);

	private:
		unsigned int m_RendererID;
	};
}
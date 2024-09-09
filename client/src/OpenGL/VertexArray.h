#pragma once

#include "OpenGL/VertexBuffer.h"

#include <glad/glad.h>

#include <vector>

/*
* When working with VAO and VBO, OpenGL it's following the next instructions in it's context:
* 1. Before creating and binding a VBO, we need to create and bind VA0. In this way the OpenGL will say 'ok, so this VBO it's assigned to the last binded VAO' or 'ok, so this VAO has been created, you need to bind a VBO to it'.
* 2. After assigning the VBO data and binding it, we need to tell OpenGL VAO details (glVertexAttribPointer): index of the starting data in the VBO, size of the data type, data type, normalized (generally false), stride and a null pointer (0)
* 3. Each VAO needs to be binded before calling draw instruction.
*/

namespace Tag2D
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Init();
		void Bind() const;
		void Unbind() const;
		void Draw() const;
		void AssingData(const VertexBuffer& vertex_buffer);

	private:
		unsigned int m_RendererID;
	};
}
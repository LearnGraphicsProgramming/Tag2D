#pragma once

#include <Entities/Triangle.h>
#include <OpenGL/Shader.h>

#include <vector>

namespace Tag2D
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		void Init();
		void OnUpdate();

	private:
		void Draw();
	
	private:
		std::vector<Triangle> m_Triangles;
		Shader m_Shader;
	};
}
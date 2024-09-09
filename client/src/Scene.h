#pragma once

#include "Camera.h"
#include <OpenGL/Shader.h>

#include <vector>
#include <memory>

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
		std::shared_ptr<Shader> m_Shader;
		Camera m_Camera;
	};
}
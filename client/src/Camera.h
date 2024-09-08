#pragma once

#include "OpenGL/OrthographicProjection.h"
#include "OpenGL/Shader.h"

#include <memory>

namespace Tag2D
{
	class Camera
	{
	public:
		Camera();
		~Camera();

		void SetShader(const std::shared_ptr<Shader>& shader);
		void Init();
		void OnUpdate();

	private:
		void CheckMovement();

	private:
		std::shared_ptr<Shader> m_Shader;
		OrthographicProjection m_OrtoProjection;

		glm::vec3 m_Position;
		float m_Speed;
	};
}
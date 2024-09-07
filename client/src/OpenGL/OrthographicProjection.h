#pragma once

#include "OpenGL/Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>

namespace Tag2D
{
	class OrthographicProjection
	{
	public:
		OrthographicProjection();
		~OrthographicProjection();

		void SetShader(const std::shared_ptr<Shader>& shader);
		void SetProjection(const float& left, const float& right, const float& bottom, const float& top, const float& z_near, const float& z_far);
		void SetView(const float& value);
		void SetModel(const float& value);
		void BindMVPMatrix();

	private:
		void CalculateMVPMatrix();

	private:
		glm::mat4 m_Projection;
		glm::mat4 m_View;
		glm::mat4 m_Model;
		glm::mat4 m_MVPMatrix;

		std::shared_ptr<Shader> m_Shader;
	};
}
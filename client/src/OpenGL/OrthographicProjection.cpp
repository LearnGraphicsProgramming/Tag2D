#include "OrthographicProjection.h"

namespace Tag2D
{
	OrthographicProjection::OrthographicProjection()
		: m_MVPMatrix(), m_Projection(), m_View(), m_Model(), m_Shader(nullptr)
	{}

	OrthographicProjection::~OrthographicProjection() {}

	void OrthographicProjection::SetShader(const std::shared_ptr<Shader>& shader)
	{
		m_Shader = shader;
	}

	void OrthographicProjection::SetProjection(const float& left, const float& right, const float& bottom, const float& top, const float& z_near, const float& z_far)
	{
		m_Projection = glm::ortho(left, right, bottom, top, z_near, z_far);
		CalculateMVPMatrix();
	}

	void OrthographicProjection::SetView(const glm::mat4& value)
	{
		m_View = value;
		CalculateMVPMatrix();
	}

	void OrthographicProjection::SetModel(const float& value)
	{
		m_Model = glm::mat4(value);
		CalculateMVPMatrix();
	}

	void OrthographicProjection::BindMVPMatrix()
	{
		m_Shader->SetUniformMatrix4fv("u_MVP", m_MVPMatrix);
	}

	void OrthographicProjection::CalculateMVPMatrix()
	{
		m_MVPMatrix = m_Projection * m_View * m_Model;
	}
}
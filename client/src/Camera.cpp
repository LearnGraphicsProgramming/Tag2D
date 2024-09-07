#include "Camera.h"
#include "Logger.h"

namespace Tag2D
{
	Camera::Camera() 
		: m_Shader(nullptr), m_OrtoProjection()
	{}

	Camera::~Camera() {}

	void Camera::SetShader(const std::shared_ptr<Shader>& shader)
	{
		m_Shader = shader;
	}

	void Camera::Init()
	{
		m_OrtoProjection.SetShader(m_Shader);
		// FIXME: Window size values should be updated
		m_OrtoProjection.SetProjection(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
		m_OrtoProjection.SetModel(1.0f);
		m_OrtoProjection.SetView(1.0f);
	}

	void Camera::OnUpdate()
	{
		m_OrtoProjection.BindMVPMatrix();
	}
}
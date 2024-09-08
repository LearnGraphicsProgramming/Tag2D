#include "Camera.h"
#include "Logger.h"
#include "Input.h"

namespace Tag2D
{
	Camera::Camera() 
		: m_Shader(nullptr), m_OrtoProjection(), m_Position(glm::vec3(0.0f, 0.0f, 1.0f)), m_Speed(1.0f)
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
		m_OrtoProjection.SetProjection(0.0f, 1280.0f, 0.0f, 720.0f, 0.1f, 1000.0f);
		m_OrtoProjection.SetModel(1.0f);
		m_OrtoProjection.SetView(glm::mat4(1.0f));
	}

	void Camera::OnUpdate()
	{
		CheckMovement();
	}

	void Camera::CheckMovement()
	{
		if (Input::Instance().KeyPress(GLFW_KEY_W))
		{
			m_Position.y -= m_Speed; // Move up
			log_info("Camera position: x=%2.f, y=%2.f, z=%2.f", m_Position.x, m_Position.y, m_Position.z);
		}

		if (Input::Instance().KeyPress(GLFW_KEY_A))
		{
			m_Position.x += m_Speed; // Move left
			log_info("Camera position: x=%2.f, y=%2.f, z=%2.f", m_Position.x, m_Position.y, m_Position.z);
		}

		if (Input::Instance().KeyPress(GLFW_KEY_S))
		{
			m_Position.y += m_Speed; // Move down
			log_info("Camera position: x=%2.f, y=%2.f, z=%2.f", m_Position.x, m_Position.y, m_Position.z);
		}

		if (Input::Instance().KeyPress(GLFW_KEY_D))
		{
			m_Position.x -= m_Speed; // Move right
			log_info("Camera position: x=%2.f, y=%2.f, z=%2.f", m_Position.x, m_Position.y, m_Position.z);
		}

		if (Input::Instance().KeyPress(GLFW_KEY_Z))
		{
			m_Position.z += m_Speed; // Move right
			log_info("Camera position: x=%2.f, y=%2.f, z=%2.f", m_Position.x, m_Position.y, m_Position.z);
		}

		if (Input::Instance().KeyPress(GLFW_KEY_X))
		{
			m_Position.z -= m_Speed; // Move right
			log_info("Camera position: x=%2.f, y=%2.f, z=%2.f", m_Position.x, m_Position.y, m_Position.z);
		}

		// FIXME: Camera logic it's not finished yet

		glm::vec3 target(m_Position.x, m_Position.y, m_Position.z - 1.0f);
		glm::vec3 up(0.0f, 1.0f, 0.0f); 

		glm::mat4 view = glm::lookAt(m_Position, target, up);

		m_OrtoProjection.SetView(view);

		m_OrtoProjection.BindMVPMatrix();
	}
}
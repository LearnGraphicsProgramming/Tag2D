#include "Scene.h"
#include "Logger.h"
#include "Application.h"

namespace Tag2D
{
	Scene::Scene()
	 : m_Shader(std::make_shared<Shader>()), m_Camera() {}

	Scene::~Scene()
	{
	}

	void Scene::Init()
	{
		if (!m_Shader->InitShader("ortho_vertex_shader.ver", "fragment_shader.frag"))
		{
			Application::Instance().Shutdown();
			return;
		}

		m_Camera.SetShader(m_Shader);
		m_Camera.Init();
	}

	void Scene::OnUpdate()
	{
		m_Shader->Bind();
		m_Camera.OnUpdate();
		Draw();
	}

	void Scene::Draw()
	{
	}
}
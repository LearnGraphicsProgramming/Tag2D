#include "Scene.h"
#include "Logger.h"
#include "Application.h"

namespace Tag2D
{
	Scene::Scene()
	 : m_Shader(std::make_shared<Shader>()), m_Camera() {}

	Scene::~Scene()
	{
		m_Triangles.clear();
	}

	void Scene::Init()
	{
		//if (!m_Shader.InitShader("vertex_shader.ver", "fragment_shader.frag"))
		if (!m_Shader->InitShader("ortho_vertex_shader.ver", "fragment_shader.frag"))
		{
			Application::Instance().Shutdown();
			return;
		}

		m_Camera.SetShader(m_Shader);
		m_Camera.Init();

		float positions[] = {
			400.0f, 300.0f, 0.0f,  // Top-right edge
			500.0f, 200.0f, 0.0f,  // Bottom-right edge
			400.0f, 200.0f, 0.0f,  // Bottom-left edge
		};

		float positions2[] = {
			300.0f, 300.0f, 0.0f,  // Top-left edge
			200.0f, 300.0f, 0.0f,  // Middle-left edge
			300.0f, 200.0f, 0.0f,  // Bottom-left edge
		};

		log_info("Creating scene entities")

		Triangle triangle1;
		triangle1.AssignVertices(positions, sizeof(positions));
		triangle1.SetID(m_Triangles.size() + 1);
		m_Triangles.push_back(triangle1);

		Triangle triangle2;
		triangle2.AssignVertices(positions2, sizeof(positions2));
		triangle2.SetID(m_Triangles.size() + 1);
		m_Triangles.push_back(triangle2);
	}

	void Scene::OnUpdate()
	{
		m_Shader->Bind();
		m_Camera.OnUpdate();
		Draw();
	}

	void Scene::Draw()
	{
		m_Shader->Bind();

		for (const auto& triangle : m_Triangles)
		{
			triangle.Draw(); // Pass the model matrix
		}
	}
}
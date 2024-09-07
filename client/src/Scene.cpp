#include "Scene.h"
#include "Logger.h"
#include "Application.h"

namespace Tag2D
{
	Scene::Scene() {}

	Scene::~Scene()
	{
		m_Triangles.clear();
	}

	void Scene::Init()
	{
		if (!m_Shader.InitShader("vertex_shader.ver", "fragment_shader.frag"))
		{
			Application::Instance().Shutdown();
			return;
		}

		float positions[] =
		{
			 0.5f,  0.5f, 0.0f,  // Top-right corner of the first triangle
			 0.9f,  0.0f, 0.0f,  // Middle-right edge
			 0.5f, -0.5f, 0.0f,  // Bottom-right corner
		};

		float positions2[] =
		{
			-0.5f,  0.5f, 0.0f,  // Top-left corner of the second triangle
			-0.9f,  0.0f, 0.0f,  // Middle-left edge
			-0.5f, -0.5f, 0.0f,  // Bottom-left corner
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
		m_Shader.Bind();
		Draw();
	}

	void Scene::Draw()
	{
		for (const auto& triangle : m_Triangles)
		{
			triangle.Draw();
		}
	}
}
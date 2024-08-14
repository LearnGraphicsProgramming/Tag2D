#include "Globals.h"
#include "Window.h"
#include "Entity.h"

#include <iostream>

int main()
{
	InitGlobals();

	log_info("!rTest");

	Tag2D::WindowProperties properties = { "Tag2D Client", "", 1280, 720 };
	std::shared_ptr<Tag2D::Window> window = std::make_shared<Tag2D::Window>(properties);

	window->SetVSync(true);

	Tag2D::Entity entity = Tag2D::Entity(window);
	entity.m_Vertices = std::vector<float>(
		{
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		}
	);

	Tag2D::Entity entity2 = Tag2D::Entity(window);
	entity2.m_Vertices = std::vector<float>(
		{
			0.5f, 0.5f, 1.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		}
	);

	window->Start();

	return 0;
}
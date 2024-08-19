#include "Cube.h"

namespace Tag2D
{
	Cube::Cube()
	{
		SetVertices({
			-0.5f,  0.5f, 0.0f, // Top-left corner
			 0.5f,  0.5f, 0.0f, // Top-right corner
			-0.5f, -0.5f, 0.0f, // Bottom-left corner
			 0.5f, -0.5f, 0.0f,  // Bottom-right corner
			});

		SetEntityClassName("cube_1");
	}

	Cube::~Cube()
	{
	}

	void Cube::OnStart()
	{
	
	}

	void Cube::OnUpdate()
	{
	}

	void Cube::OnClose()
	{
	}
}
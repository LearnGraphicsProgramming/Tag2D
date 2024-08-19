#include "Square.h"

namespace Tag2D
{
	Square::Square()
	{
		SetVertices({
			-0.5f,  0.5f, 0.0f, // Top-left corner
			 0.5f,  0.5f, 0.0f, // Top-right corner
			-0.5f, -0.5f, 0.0f, // Bottom-left corner
			 0.5f, -0.5f, 0.0f,  // Bottom-right corner
			});

		SetEntityClassName("cube_1");
	}

	Square::~Square()
	{
	}

	void Square::OnStart()
	{
	
	}

	void Square::OnUpdate()
	{
	}

	void Square::OnClose()
	{
	}
}
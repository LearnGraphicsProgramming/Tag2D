#include "Globals.h"
#include "Window.h"

#include <iostream>

int main()
{
	InitGlobals();

	log_info("!rTest");

	Window window({"Tag2D Client", "", 1280, 720 });
	window.SetVSync(true);

	while (!glfwWindowShouldClose(window.GetGLFWWindow()))
	{
		glClearColor(1.0f, 0.0f, 0.54901960784f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		window.OnUpdate();
	}

	return 0;
}
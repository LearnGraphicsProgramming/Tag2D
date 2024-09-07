#include "Globals.h"
#include <Application.h>

#include <iostream>

int main()
{
	InitGlobals();

	Tag2D::Application::Instance().Init();

	Tag2D::Application::Instance().Run();
}
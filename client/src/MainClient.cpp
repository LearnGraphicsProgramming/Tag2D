#include "Globals.h"
#include <Application.h>

#include <iostream>

int main()
{
	InitGlobals();

	Tag2D::Application gameApp = Tag2D::Application();
	gameApp.Init();

	return 0;
}
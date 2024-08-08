#include <memory>

#include "Server.h"
#include "Console.h"
#include "Globals.h"
#include "FrameCounter.h"

void dummy_command()
{
	std::cout << "Dummy command called!\n";
}

int main()
{
	InitGlobals();

	std::shared_ptr<Tag2D::Server> server = std::make_shared<Tag2D::Server>();
	server->Init(SERVER_ADDRESS, SERVER_PORT);

	std::shared_ptr<Tag2D::Console> console = std::make_shared<Tag2D::Console>();
	std::shared_ptr<FrameCounter> frameCounter = std::make_shared<FrameCounter>();

	server->RegisterOnFrameCallback([console]() { console->OnFrame(); });
	server->RegisterOnFrameCallback([frameCounter]() { frameCounter->OnFrame(); });

	server->Start();

	server.reset();
}
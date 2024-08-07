#include <memory>

#include "Server.h"
#include "Console.h"
#include "Globals.h"

void dummy_command()
{
	std::cout << "Dummy command called!\n";
}

int main()
{
	InitGlobals();

	std::unique_ptr<Tag2D::Console> console = std::make_unique<Tag2D::Console>();

	console->RegisterCommand("dummy_cmd", &dummy_command);

	std::shared_ptr<Tag2D::Server> server = std::make_shared<Tag2D::Server>();
	server->Init(SERVER_ADDRESS, SERVER_PORT);

	server->RegisterOnFrameCallback(std::bind(&Tag2D::Console::OnFrame, console.get()));

	server->Start();

	server.reset();
}
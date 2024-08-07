#include <memory>

#include "Server.h"
#include "Console.h"
#include "Globals.h"

int main()
{
	InitGlobals();

	std::shared_ptr<Tag2D::Server> server = std::make_shared<Tag2D::Server>();
	server->Init(SERVER_ADDRESS, SERVER_PORT);
	server->Start();

	server.reset();
}
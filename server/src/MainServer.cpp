#include <memory>
#include "Server.h"

int main()
{
	std::unique_ptr<Tag2D::Server> server = std::make_unique<tag::Server>();

	server.reset();
}
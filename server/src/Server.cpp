#include "Server.h"
#include <iostream>

namespace Tag2D
{
	Server::Server()
		: m_ShouldRun(false), m_Address{}, m_Port(-1)
	{
		std::cout << "Creating server object...\n";
	}

	Server::~Server()
	{
		std::cout << "Deleting server object...\n";
	}

	void Server::Init(char* address, uint16_t port)
	{
		strncpy_s(m_Address, sizeof(m_Address), address, MAX_IP_ADDRESS_LENGTH - 1);
		m_ShouldRun = true;
	}

	void Server::Start()
	{
		while (true)
		{
			OnFrame();
		}
	}

	void Server::Stop()
	{
		m_ShouldRun = true;
	}

	void Server::OnFrame()
	{

	}
}
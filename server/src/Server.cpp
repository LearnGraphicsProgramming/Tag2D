#include "Server.h"
#include <iostream>

namespace Tag2D
{
	Server::Server()
		: m_ShouldRun(false), m_Address{}, m_Port(-1), m_Frame(0)
	{
		std::cout << "Creating server object...\n";
	}

	Server::~Server()
	{
		Stop();
	}

	void Server::Init(const char* address, uint16_t port)
	{
		std::cout << "Initializing server object...\n";

		strncpy_s(m_Address, sizeof(m_Address), address, MAX_IP_ADDRESS_LENGTH - 1);
		m_ShouldRun = true;
	}

	void Server::Start()
	{
		while (m_ShouldRun)
		{
			OnFrame();
		}
	}

	void Server::Stop()
	{
		std::cout << "Stopping server object...\n";
		m_ShouldRun = true;
	}

	void Server::OnFrame()
	{
		m_Frame += 1;
		std::cout << "Server OnFrame " << m_Frame << "\n";
	}
}
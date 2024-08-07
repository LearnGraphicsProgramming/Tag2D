#include "Server.h"
#include "Logger.h"
#include <iostream>

namespace Tag2D
{
	Server::Server()
		: m_ShouldRun(false), m_Frame(0), m_Socket(Socket())
	{
		log_info("Created socket object");
	}

	Server::~Server()
	{
		Stop();
	}

	void Server::Init(const char* address, uint16_t port)
	{
		log_info("Initializing server object...\n");

		if (!m_Socket.Init(address, port))
		{
			log_error("Server can't be initialized because of socket error.");
			return;
		}

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
		log_info("Stopping server...");
		m_ShouldRun = true;
	}

	void Server::OnFrame()
	{
		m_Frame += 1;
	
		m_Socket.OnFrame();
	}
}
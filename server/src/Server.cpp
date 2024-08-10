#include "Server.h"
#include "../../common/src/Logger.h"
#include <iostream>

namespace Tag2D
{
	Server::Server()
		: m_ShouldRun(false), m_Socket(Socket())
	{
		log_info("Created socket object");
	}

	Server::~Server()
	{
		Stop();
	}

	bool Server::Init(const char* address, uint16_t port)
	{
		log_info("Initializing server object...\n");

		
		// Initializing socket.
		if (!m_Socket.Init(address, port))
		{
			// Don't run the server if the socket has not been initialized
			log_error("Server can't be initialized.");
			return false;
		}

		m_ShouldRun = true;
		
		return true;
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

	void Server::RegisterOnFrameCallback(OnFrameCallbackFn callback)
	{
		m_OnFrameCallbacks.push_back(callback);

		log_info("New!w OnFrame Callback!d function has been added");
	}

	void Server::OnFrame()
	{
		// Calling OnFrame function of the socket object. Currently disabled because the socket it's in blocking mode (it will block the server until a new connection will be made).
		//m_Socket.OnFrame();

		for (const auto& function : m_OnFrameCallbacks)
		{
			function();
		}
	}
}

#ifndef SERVER_H
#define SERVER_H

#include "pc.h"
#include "Logger.h"

#include <cstdint>
#include <functional>
#include <vector>

#include "Socket.h"

class Socket;

namespace Tag2D
{
	// The main class of the server. It is responsible with managing players data. Also, here is the server loop.

	class Server
	{
	public:
		Server();
		~Server();

		void Init(const char* address, uint16_t port);
		void Start();
		void Stop();

	private:
		void OnFrame();

	private:
		bool m_ShouldRun;
		uint64_t m_Frame;

		Socket m_Socket;
	};
}

#endif // SERVER_H
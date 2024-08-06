#ifndef SERVER_H
#define SERVER_H

#include <cstdint>
#include <functional>
#include <vector>

#include "pc.h"

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

		char m_Address[MAX_IP_ADDRESS_LENGTH];
		uint16_t m_Port;

		uint64_t m_Frame;
	};
}

#endif // SERVER_H
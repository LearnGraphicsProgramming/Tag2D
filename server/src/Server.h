#ifndef SERVER_H
#define SERVER_H

#include <cstdint>
#include "pc.h"

namespace Tag2D
{
	class Server
	{
	public:
		Server();
		~Server();

		void Init(char* address, uint16_t port);
		void Start();
		void Stop();

	private:
		void OnFrame();

	private:
		bool m_ShouldRun;

		char m_Address[MAX_IP_ADDRESS_LENGTH];
		uint16_t m_Port;
	};
}

#endif // SERVER_H
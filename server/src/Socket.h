#ifndef SOCKET_H
#define SOCKET_H

#include "pc.h"

#include <cstdint>
#include <string>

#ifdef WINDOWS
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#endif

#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif

// TODO: Add non-blocking option

namespace Tag2D
{
	// Multi-platform Socket object
	class Socket
	{
	public:
		Socket();
		virtual ~Socket();

		bool Init(const char* address, uint16_t port);
		void OnFrame() const;
	
	private:
		char m_Address[MAX_IP_ADDRESS_LENGTH];
		uint16_t m_Port;

#ifdef WINDOWS
		WSADATA m_WSAData;
#endif
		sockaddr_in m_SocketAddrStruct;

		uint64_t m_ListenSocket;
	};
}
#endif // SOCKET_H
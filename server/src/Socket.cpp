#include "Socket.h"
#include "Logger.h"

namespace Tag2D
{
	Socket::Socket()
		: m_Address{ 0 }, m_Port(-1), m_ListenSocket(INVALID_SOCKET), m_SocketAddrStruct(sockaddr_in())
#ifdef WINDOWS
		,m_WSAData(WSADATA())
#endif
	{}

	Socket::~Socket()
	{
#ifdef WINDOWS
		WSACleanup();
		closesocket(m_ListenSocket);
#else
		close(m_ListenSocket);
#endif
	}

	bool Socket::Init(const char* address, uint16_t port)
	{
		int result = SOCKET_ERROR;

		// Init WSA API for Windows. 
#ifdef WINDOWS
		result = WSAStartup(MAKEWORD(2, 2), &m_WSAData);

		if (result != 0)
		{
			log_error("Failed to start Windows WSA");
			return false;
		}
#endif

		// Creating a socket on the machine and get it's descriptor (descriptor  = index, id.. etc)
		m_ListenSocket = socket(AF_INET, SOCK_STREAM, 0);

		if (m_ListenSocket == SOCKET_ERROR)
		{
			log_error("Failed to create socket (no socket descriptor returned)");
			return false;
		}

		strncpy_s(m_Address, sizeof(m_Address), address, MAX_IP_ADDRESS_LENGTH - 1);
		m_Port = port;
		
		// Creating a socket address structure which will contain informations about the socket we want to create
		memset(&m_SocketAddrStruct, 0, sizeof(m_SocketAddrStruct));
		m_SocketAddrStruct.sin_family = AF_INET; // AF -> Address Family. AF_INET = for IPv4 address and AF_INET6 for IPv6 address
		m_SocketAddrStruct.sin_port = htons(m_Port); // port
		inet_pton(AF_INET, m_Address, &m_SocketAddrStruct.sin_addr); // adding the address (defined in pc.h)

		// Trying to bind the informations we want to the socket
		if (bind(m_ListenSocket, (sockaddr*)&m_SocketAddrStruct, sizeof(m_SocketAddrStruct)) == SOCKET_ERROR)
		{
			//a SOCKET_ERROR (which is -1) will be returned with an error code
			log_error("Failed to bind socket");
			return false;
		}

		// Marking the socket as a listening sockets (which can accept connections)
		if (listen(m_ListenSocket, SOMAXCONN) == SOCKET_ERROR)
		{
			log_error("Failed to listen");
			return false;
		}

		log_info("!gServer listening at %s:%i", m_Address, m_Port);	
		return true;
	}

	// This function it's registered in the server and will be called at every frame
	void Socket::OnFrame() const
	{
		sockaddr_in clientSocketAddr{};
		int clientSocketAddrSize = sizeof(clientSocketAddr);

		// Accept the connection and get it's value (currently blocking)
		SOCKET clientSocket = accept(m_ListenSocket, (sockaddr*)&clientSocket, &clientSocketAddrSize);

		if (clientSocket != INVALID_SOCKET)
		{
			log_info("New connection to the server!");
			closesocket(clientSocket);
		}
	}
}

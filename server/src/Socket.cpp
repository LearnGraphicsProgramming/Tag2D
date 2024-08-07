#include "Socket.h"
#include "Logger.h"

namespace Tag2D
{
	Socket::Socket()
		: m_Address{ 0 }, m_Port(-1), m_ListenSocket(INVALID_SOCKET), m_SocketAddrStruct(sockaddr_in())
#ifdef WINDOWS
		, m_WSAData(WSADATA())
#endif
	{
#ifdef DEBUG
		log_info("Creating server object...");
#endif
	}

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
		log_info("Initializing socket..");

#ifdef WINDOWS
		result = WSAStartup(MAKEWORD(2, 2), &m_WSAData);

		if (result != 0)
		{
			log_error("Failed to start Windows WSA");
			return false;
		}
#endif

		m_ListenSocket = socket(AF_INET, SOCK_STREAM, 0);

		if (m_ListenSocket == SOCKET_ERROR)
		{
			log_error("Failed to create socket (no socket descriptor returned)");
			return false;
		}

		strncpy_s(m_Address, sizeof(m_Address), address, MAX_IP_ADDRESS_LENGTH - 1);
		m_Port = port;
		
		memset(&m_SocketAddrStruct, 0, sizeof(m_SocketAddrStruct));
		m_SocketAddrStruct.sin_family = AF_INET;
		m_SocketAddrStruct.sin_port = htons(m_Port);
		inet_pton(AF_INET, m_Address, &m_SocketAddrStruct.sin_addr);

		if (bind(m_ListenSocket, (sockaddr*)&m_SocketAddrStruct, sizeof(m_SocketAddrStruct)) == SOCKET_ERROR)
		{
			log_error("Failed to bind socket");
			return false;
		}

		if (listen(m_ListenSocket, SOMAXCONN) == SOCKET_ERROR)
		{
			log_error("Failed to listen");
			return false;
		}

		log_info("Server listening at ");
		std::cout << address << ":" << port << "\n";
		
		return true;
	}

	void Socket::OnFrame() const
	{
		sockaddr_in clientSocketAddr{};
		int clientSocketAddrSize = sizeof(clientSocketAddr);

		SOCKET clientSocket = accept(m_ListenSocket, (sockaddr*)&clientSocket, &clientSocketAddrSize);

		if (clientSocket != INVALID_SOCKET)
		{
			log_info("New connection to the server!");
			closesocket(clientSocket);
		}
		else
		{
#ifdef WINDOWS
			log_error(std::to_string(WSAGetLastError()));
#else
			perror("accept");
#endif
		}
	}
}
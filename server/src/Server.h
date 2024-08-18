#ifndef SERVER_H
#define SERVER_H

#include "../../common/src/pc.h"

#include <cstdint>
#include <functional>
#include <vector>

#include "Socket.h"
#include "../../common/src/Timestep.h"

class Socket;

namespace Tag2D
{
	// The main class of the server. It is responsible with managing players data. Also, here is the server loop.
	using OnFrameCallbackFn = std::function<void()>;

	class Server
	{
	public:
		Server();
		~Server();

		bool Init(const char* address, uint16_t port);
		void Start();
		void Stop();

		void RegisterOnFrameCallback(OnFrameCallbackFn callback);

	private:
		void OnFrame();

	private:
		bool m_ShouldRun;

		Socket m_Socket;
		std::vector<OnFrameCallbackFn> m_OnFrameCallbacks;
	};
}

#endif // SERVER_H

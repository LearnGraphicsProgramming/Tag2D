#ifndef SERVER_H
#define SERVER_H

#include "pc.h"

#include <cstdint>
#include <functional>
#include <vector>

#include "Socket.h"
#include <Timestep.h>

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

		void Init(const char* address, uint16_t port);
		void Start();
		void Stop();

		void RegisterOnFrameCallback(OnFrameCallbackFn callback);
		inline const uint64_t& GetFrames() const { return m_Frame; }
		inline std::shared_ptr<Timestep> GetLastFrameTimestamp() const { return m_LastFrameTimestamp; }

	private:
		void OnFrame();

	private:
		bool m_ShouldRun;
		uint64_t m_Frame;

		Socket m_Socket;
		std::vector<OnFrameCallbackFn> m_OnFrameCallbacks;

		std::shared_ptr<Timestep> m_LastFrameTimestamp;
	};
}

#endif // SERVER_H
#ifndef APPLICATION_H
#define APPLICATION_H

#include "Window.h"
#include "Scene.h"

#include <memory>
#include <vector>

namespace Tag2D
{
	class BaseEntity;

	class Application
	{
	public:
		Application();
		~Application();
		static Application& Instance();

		void Init();
		void Run();

	private:
		static Application m_Instance;
		std::shared_ptr<Window> m_Window;

		std::unique_ptr<Scene> m_ActiveScene;
	};
}

#endif // APPLICATION_H
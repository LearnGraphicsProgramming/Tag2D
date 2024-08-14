#ifndef APPLICATION_H
#define APPLICATION_H

#include "Window.h"
#include "Entity.h"

#include <memory>
#include <vector>

namespace Tag2D
{
	class Application
	{
	public:
		Application();
		~Application();

		void Init();
		void Run();

	private:
		std::shared_ptr<Window> m_Window;

		std::vector<BaseEntity> m_Entities;
	};
}

#endif // APPLICATION_H
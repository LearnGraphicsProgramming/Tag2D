#ifndef APPLICATION_EVENTS_H
#define APPLICATION_EVENTS_H

#include <string>

#define GetEventName(type) (std::string("Name index: " + std::to_string(static_cast<int>(type)))

//const char* WINDOW_EVENT_DICTIONARY[] =
//{
//	{ "Window::OnStart" },
//	{ "Window::OnUpdate" },
//	{ "Window::OnClose" }
//};

namespace Tag2D
{

	enum class ApplicationEventType
	{
		Start = 0,
		Update,
		Close
	};
}



#endif // APPLICATION_EVENTS_H
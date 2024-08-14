#ifndef WINDOW_H
#define WINDOW_H

#include "pc.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <functional>
#include <unordered_map>

#include "Shaders.h"

#define GetEventName(type) (WINDOW_EVENT_DICTIONARY[static_cast<int>(type)].c_str())

namespace Tag2D
{
	struct WindowProperties
	{
		std::string Title;
		std::string IconPath;
		int Width;
		int Height;

		WindowProperties(const std::string& title = "",
			std::string iconPath = "",
			int width = 1280,
			int height = 720)
			: Title(title), IconPath(iconPath), Width(width), Height(height)
		{
		}

		virtual ~WindowProperties() = default;
	};

	enum class WindowEventType
	{
		Start = 0,
		Update,
		Close
	};

	const std::string WINDOW_EVENT_DICTIONARY[] =
	{
		{ "Window::OnStart" },
		{ "Window::OnUpdate" },
		{ "Window::OnClose" }

	};

	class Window
	{
		using EventCallbackFn = std::function<void()>;
	public:
		Window(const WindowProperties& properties = WindowProperties());
		virtual ~Window();

		virtual void OnUpdate();

		virtual void SetVSync(bool enabled);
		virtual bool IsVSync() const { return m_Data.VSync; }

		virtual const std::string& GetTitle() const { return m_Data.Title; }
		virtual void SetTitle(const std::string& title);

		virtual const std::string& GetIconPath() const { return m_Data.IconPath; }
		virtual void SetIconPath(const std::string& iconPath);

		virtual uint32_t GetWidth() const { return m_Data.Width; }
		virtual uint32_t GetHeight() const { return m_Data.Height; }
		virtual std::pair<uint32_t, uint32_t> GetSize() const { return { m_Data.Width, m_Data.Height }; }
		virtual std::pair<float, float> GetWindowPosition() const;

		virtual GLFWwindow* GetGLFWWindow() const { return m_Window; }
		virtual const bool ShouldClose() const { return glfwWindowShouldClose(m_Window) != 0; }

		virtual void LoadIcon(const std::string& iconPath);

		virtual void Start();
		static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

		void RegisterWindowCallback(const WindowEventType& type, EventCallbackFn function);
		void UnregisterWindowCallback(std::unordered_map<WindowEventType, int>& class_callback_ids);
		void TriggerEventCallback(const WindowEventType& type) const;

	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			GLFWimage Icon[1];
			std::string IconPath;
			uint32_t Width, Height;
			bool VSync;
		} m_Data;

		float m_LastFrameTime = 0.0f;
		Shaders m_Shaders;

		std::unordered_map<
			WindowEventType,
			std::vector<EventCallbackFn>
		> m_EventsCallbacks;
	};
}

#endif // WINDOW_H
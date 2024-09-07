#ifndef WINDOW_H
#define WINDOW_H

#include "pc.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

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

		 ~WindowProperties() = default;
	};

	class Window
	{
	public:
		Window(const WindowProperties& properties = WindowProperties());
		~Window();

		void OnUpdate();
		inline void Close() { glfwSetWindowShouldClose(m_Window, true); }
		void OnUpdatePost();

		void SetVSync(bool enabled);
		bool IsVSync() const { return m_Data.VSync; }

		const std::string& GetTitle() const { return m_Data.Title; }
		void SetTitle(const std::string& title);

		const std::string& GetIconPath() const { return m_Data.IconPath; }
		void SetIconPath(const std::string& iconPath);

		uint32_t GetWidth() const { return m_Data.Width; }
		uint32_t GetHeight() const { return m_Data.Height; }
		std::pair<uint32_t, uint32_t> GetSize() const { return { m_Data.Width, m_Data.Height }; }
		std::pair<float, float> GetWindowPosition() const;

		GLFWwindow* GetGLFWWindow() const { return m_Window; }
		const bool ShouldClose() const { return glfwWindowShouldClose(m_Window) != 0; }

		void LoadIcon(const std::string& iconPath);
		static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

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
	};
}

#endif // WINDOW_H
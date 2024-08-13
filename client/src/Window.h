#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

struct WindowProperties
{
	std::string Title;
	std::string IconPath;
	uint32_t Width;
	uint32_t Height;

	WindowProperties(const std::string& title = "",
		std::string iconPath = "",
		uint32_t width = 1280,
		uint32_t height = 720)
		: Title(title), IconPath(iconPath), Width(width), Height(height)
	{
	}

	virtual ~WindowProperties() = default;
};

class Window
{
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


private:
	virtual void LoadIcon(const std::string& iconPath);

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

#endif // WINDOW_H
#include "Shaders.h"
#include "Logger.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Tag2D
{
	Shaders::Shaders()
		: m_VertexShader(0), m_FragmentShader(0), m_ShaderProgram(0) {}

	Shaders::~Shaders()
	{
		glDeleteProgram(m_ShaderProgram);
	}

	const bool Shaders::InitShaders()
	{
		if (!InitVertexShader())
		{
			return false;
		}

		if (!InitFragmentShader())
		{
			glDeleteShader(m_VertexShader);
			return false;
		}

		m_ShaderProgram = glCreateProgram();

		glAttachShader(m_ShaderProgram, m_VertexShader);
		glAttachShader(m_ShaderProgram, m_FragmentShader);
		glLinkProgram(m_ShaderProgram);

		glDeleteShader(m_VertexShader);
		glDeleteShader(m_FragmentShader);

		glUseProgram(m_ShaderProgram);

		log_info("Shaders initialized succesfully");

		return true;
	}

	const bool Shaders::InitVertexShader()
	{
		const char* vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"}\0";

		m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
		
		glShaderSource(m_VertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(m_VertexShader);

		char infoLog[512];
		int success;
		glGetShaderiv(m_VertexShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(m_VertexShader, 512, NULL, infoLog);
			log_error("Failed to compile Vertex Shader. Info log: %s", infoLog);
		}

		return static_cast<bool>(success);
	}

	const bool  Shaders::InitFragmentShader()
	{
		const char* fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"	FragColor = vec4(1.0f, 0.8f, 0.2f, 1.0f);\n"
			"}\0";

		m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(m_FragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(m_FragmentShader);
		
		char infoLog[512];
		int success;
		
		glGetShaderiv(m_FragmentShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(m_FragmentShader, 512, NULL, infoLog);
			log_error("Failed to compile Fragment Shader. Info log: %s", infoLog);
		}

		return static_cast<bool>(success);
	}
}

#include "Shader.h"
#include "Logger.h"

#include <filesystem>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Tag2D
{
	Shader::Shader()
		: m_VertexShader(0), m_FragmentShader(0), m_ShaderProgram(0) {}

	Shader::~Shader()
	{
		glDeleteProgram(m_ShaderProgram);
	}

	const bool Shader::InitShader()
	{
		std::string VertexShader = LoadShaderSourceFromFile("vertex_shader.frag");

		if (VertexShader.size() == 0)
		{
			log_warning("Vertex Shader initialization failed, closing program");
			return false;
		}
		
		std::string FragmentShader = LoadShaderSourceFromFile("fragment_shader.frag");

		if (FragmentShader.size() == 0)
		{
			log_warning("Fragment Shader initialization failed, closing program");
			return false;
		}

		if (!CompileShader(m_VertexShader, VertexShader, GL_VERTEX_SHADER))
		{
			log_warning("Vertex Shader compiling failed, closing program");
			return false;
		}

		if (!CompileShader(m_FragmentShader, FragmentShader, GL_FRAGMENT_SHADER))
		{
			log_warning("Fragment Shader compiling failed, closing program");
			return false;
		}

		m_ShaderProgram = glCreateProgram();

		glAttachShader(m_ShaderProgram, m_VertexShader);
		glAttachShader(m_ShaderProgram, m_FragmentShader);
		glLinkProgram(m_ShaderProgram);

		glDeleteShader(m_VertexShader);
		glDeleteShader(m_FragmentShader);

		glUseProgram(m_ShaderProgram);

		log_info("[Shader] Initialized succesfully");

		return true;
	}

	const bool Shader::CompileShader(unsigned int& index, std::string& source, int type)
	{
		index = glCreateShader(type);
	
		const char* ShaderSource = source.c_str();
		glShaderSource(index, 1, &ShaderSource, NULL);
		glCompileShader(index);

		char InfoLog[512]{}; int Success = -1;

		glGetShaderiv(index, GL_COMPILE_STATUS, &Success);

		if (!Success)
		{
			glGetShaderInfoLog(index, 512, NULL, InfoLog);
			log_error("Failed to compile !y%s Shader!d. Info log: !w%s", type == GL_FRAGMENT_SHADER ? "Fragment" : "Vertex", InfoLog);
		}

		return static_cast<bool>(Success);
	}

	std::string Shader::LoadShaderSourceFromFile(const std::string_view& file_name)
	{
		std::filesystem::path ShaderPath = std::filesystem::path("./Assets/Shaders/") / file_name.data();

		if (!std::filesystem::exists(ShaderPath))
		{
			log_error("Failed to load !y%s!d file. Current path:!w %s", ShaderPath.string().c_str(), std::filesystem::current_path().string().c_str());
			return std::string();
		}

		std::ifstream File(ShaderPath, std::ios::in | std::ios::binary);

		if (!File.is_open())
		{
			log_error("Failed to open !y%s!d file. Current path:!w %s", ShaderPath.string().c_str(), std::filesystem::current_path().string().c_str());
			return std::string();
		}

		std::string FileContent{ std::istreambuf_iterator<char>(File), std::istreambuf_iterator<char>()};
		File.close();

		return FileContent;
	}
}

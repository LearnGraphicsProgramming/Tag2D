#include "Shader.h"
#include "Logger.h"

#include <filesystem>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Tag2D
{
	Shader::Shader()
		: m_VertexShader(0), m_FragmentShader(0), m_ShaderProgram(0)
	{}

	Shader::~Shader()
	{
		Unbind();
		glDeleteProgram(m_ShaderProgram);
	}

	const bool Shader::InitShader(const std::string_view& vertex_shader_file, const std::string_view& fragment_shader_file)
	{
		std::string VertexShader = LoadShaderSourceFromFile(vertex_shader_file);
		if (VertexShader.size() == 0)
		{
			log_warning("Vertex Shader initialization failed");
			return false;
		}
		
		std::string FragmentShader = LoadShaderSourceFromFile(fragment_shader_file);
		if (FragmentShader.size() == 0)
		{
			log_warning("Fragment Shader initialization failed");
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

	void Shader::Bind() const
	{
		glUseProgram(m_ShaderProgram);
	}

	void Shader::Unbind() const
	{	
		glUseProgram(0);
	}

	unsigned int Shader::GetUniformLocation(const std::string_view& name) const
	{
		unsigned int location = glGetUniformLocation(m_ShaderProgram, name.data());

		if (location == -1)
		{
			log_error("Failed to get uniform location of !y%s", name.data());
		}

		// TODO: Cache locations in a STL container (maybe unordered map?).

		return location;
	}

	void Shader::SetUniformMatrix4fv(const std::string_view& name, const glm::mat4& value) const
	{
		unsigned int location = GetUniformLocation(name);

		if (location != -1)
		{
			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
		}
		else
		{
			log_warning("Value for !y%s!d has not been set", name.data());
		}
	}

	std::string Shader::LoadShaderSourceFromFile(const std::string_view& file_name)
	{
		// FIXME: Hack to load the file from src folder for VS debugging.
		std::filesystem::path ShaderPath = std::filesystem::path("./src/OpenGL/Shaders/") / file_name.data();
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

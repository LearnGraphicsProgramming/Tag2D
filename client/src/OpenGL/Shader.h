#ifndef SHADERS_H
#define SHADERS_H

#include <string>
#include <glm/glm.hpp>

namespace Tag2D
{
	class Shader
	{
	public:
		Shader();
		~Shader();

		const bool InitShader(const std::string_view& vertex_shader_file, const std::string_view& fragment_shader_file);
		std::string LoadShaderSourceFromFile(const std::string_view& file_name);
		const bool CompileShader(unsigned int& index, std::string& source, int type);
		
		void Bind() const;
		void Unbind() const;

		void SetUniformMatrix4fv(const std::string_view& name, const glm::mat4& value) const;

	private:
		unsigned int GetUniformLocation(const std::string_view& name) const;
	
	private:
		unsigned int m_VertexShader;
		unsigned int m_FragmentShader;
		unsigned int m_ShaderProgram;
	};
}

#endif // SHADERS_H
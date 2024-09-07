#ifndef SHADERS_H
#define SHADERS_H

#include <string>

namespace Tag2D
{
	class Shader
	{
	public:
		Shader();
		~Shader();

		const bool InitShader(const std::string_view& vertex_shader_file, const std::string_view& fragment_shader_file);
		const bool CompileShader(unsigned int& index, std::string& source, int type);
		void Bind() const;
		void Unbind() const;

		std::string LoadShaderSourceFromFile(const std::string_view& file_name);

	private:
		unsigned int m_VertexShader;
		unsigned int m_FragmentShader;
		unsigned int m_ShaderProgram;
	};
}

#endif // SHADERS_H
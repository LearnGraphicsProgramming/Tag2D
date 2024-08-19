#ifndef SHADERS_H
#define SHADERS_H

namespace Tag2D
{
	class Shaders
	{
	public:
		Shaders();
		~Shaders();

		const bool InitShaders();

		const bool InitVertexShader();
		const bool InitFragmentShader();

	private:
		unsigned int m_VertexShader;
		unsigned int m_FragmentShader;
		unsigned int m_ShaderProgram;
	};
}

#endif // SHADERS_H
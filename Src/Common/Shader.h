#ifndef __OPENGLSAMPLE_SHADER_H__
#define __OPENGLSAMPLE_SHADER_H__

#include"GL.h"
#include<string>

class Shader
{
public:
	Shader();
	Shader(const std::string& strVertexSrc, const std::string& strFragmentSrc);
	~Shader();

	bool	Load(const std::string& strVertexSrc, const std::string& strFragmentSrc);
	void	Use();
	void	UnUse();

	GLuint	GetUniformLocation(const std::string& strName);

private:
	GLuint	Compile(GLenum shaderType, const char* szSrc);
	bool	Link();

private:
	bool	m_bLoaded;
	GLuint	m_Program;
	GLuint	m_VertexShader;
	GLuint	m_FragmentShader;
};

#endif
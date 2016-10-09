#include"Shader.h"
#include<string>

Shader::Shader()
:m_bLoaded(false)
, m_Program(0)
, m_VertexShader(0)
, m_FragmentShader(0)
{

}

Shader::Shader(const std::string& strVertexSrc, const std::string& strFragmentSrc)
: m_bLoaded(false)
, m_Program(0), m_VertexShader(0)
, m_FragmentShader(0)
{
	Load(strVertexSrc, strFragmentSrc);
}

Shader::~Shader()
{
	glDeleteProgram(m_Program);
}

bool Shader::Load(const std::string& strVertexSrc, const std::string& strFragmentSrc)
{
	m_VertexShader = Compile(GL_VERTEX_SHADER, strVertexSrc.c_str());
	if (!m_VertexShader)
	{
		return false;
	}
	m_FragmentShader = Compile(GL_FRAGMENT_SHADER, strFragmentSrc.c_str());
	if (!m_FragmentShader)
	{
		return false;
	}

	m_Program = glCreateProgram();

	m_bLoaded = Link();

	return true;
}

void Shader::Use()
{
	if (m_bLoaded && m_Program)
	{
		glUseProgram(m_Program);
	}
}

void Shader::UnUse()
{
	glUseProgram(0);
}

GLuint Shader::Compile(GLenum shaderType, const char* szSrc)
{
	// 创建shader
	GLuint shaderId = glCreateShader(shaderType);
	if (shaderId <= 0)
	{
		return 0;
	}

	// 数据输入shader
	const char* src = szSrc;
	int iLen = strlen(src);
	glShaderSource(shaderId, 1, &src, &iLen);

	// 编译shader
	glCompileShader(shaderId);

	// 查看shader编译状态
	GLint status;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
	if (GL_TRUE != status)
	{
		// 获取错误信息
		char szErrorBuff[2048] = { 0 };
		GLsizei length;
		glGetShaderInfoLog(shaderId, 2048, &length, szErrorBuff);

		return 0;
	}

	return shaderId;
}

bool Shader::Link()
{
	glAttachShader(m_Program, m_VertexShader);
	glAttachShader(m_Program, m_FragmentShader);

	glLinkProgram(m_Program);

	GLint status;
	glGetProgramiv(m_Program, GL_LINK_STATUS, &status);
	if (GL_TRUE != status)
	{
		char szErrorBuff[2048] = { 0 };
		GLsizei length;
		glGetProgramInfoLog(m_Program, 2048, &length, szErrorBuff);

		return false;
	}

	glDetachShader(m_Program, m_VertexShader);
	glDetachShader(m_Program, m_FragmentShader);
	glDeleteShader(m_VertexShader);
	glDeleteShader(m_FragmentShader);

	return true;
}
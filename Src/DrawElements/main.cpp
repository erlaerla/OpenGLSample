#include"../Common/Framework.h"
#include"../Common/GL.h"
#include"../Common/Shader.h"
#include"../Common/FileLoader.h"

#pragma comment(lib, "Common.lib")
#pragma comment(lib, "Launcher.lib")

class CDrawElements : public Framework
{
public:
	CDrawElements();
	~CDrawElements();

	virtual int		Initialize();
	virtual void	Uninitialize();
	virtual void	Render();

private:
	GLuint	m_VAOId;
	GLuint	m_VBOId;
	GLuint	m_EBOId;
	Shader	m_Shader;
};

CDrawElements::CDrawElements()
	:m_VAOId(0)
	, m_VBOId(0)
	, m_EBOId(0)
{

}

CDrawElements::~CDrawElements()
{

}

int	CDrawElements::Initialize()
{
	FileLoader vertexShaderFile("shader/triangle.vertex");
	if (!vertexShaderFile.IsLoaded())
		return -1;

	FileLoader fragmentShaderFile("shader/triangle.frag");
	if (!fragmentShaderFile.IsLoaded())
		return -1;

	if (!m_Shader.Load(vertexShaderFile.GetData(), fragmentShaderFile.GetData()))
		return -1;

	GLfloat vertices[] =
	{
		-0.5f, 0.0f, 0.0f, 0.8f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f, 0.0f, 0.8f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f, 0.0, 0.8f,
		0.0f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
	};

	GLushort indices[] =
	{
		0, 1, 2,
		0, 3, 1,
	};

	//创建绑定VAO
	glGenVertexArrays(1, &m_VAOId);
	glBindVertexArray(m_VAOId);

	//创建绑定VBO
	glGenBuffers(1, &m_VBOId);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOId);

	//分配空间，传送数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//创建绑定EBO
	glGenBuffers(1, &m_EBOId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBOId);
	//分配空间，传送数据
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//指定解析方式，启动顶点属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);

	//解除绑定
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return 0;
}

void CDrawElements::Uninitialize()
{
	if (m_VAOId)
		glDeleteVertexArrays(1, &m_VAOId);
	if (m_VBOId)
		glDeleteBuffers(1, &m_VBOId);
	if (m_EBOId)
		glDeleteBuffers(1, &m_EBOId);
}

void CDrawElements::Render()
{
	glBindVertexArray(m_VAOId);
	m_Shader.Use();
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

	glBindVertexArray(0);
	m_Shader.UnUse();
}

static CDrawElements app;
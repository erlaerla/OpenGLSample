#include"../Common/Framework.h"
#include"../Common/GL.h"
#include"../Common/Shader.h"
#include"../Common/FileLoader.h"

#pragma comment(lib, "Common.lib")
#pragma comment(lib, "Launcher.lib")

class CDrawTriangles : public Framework
{
public:
	CDrawTriangles();
	~CDrawTriangles();
	
	virtual int		Initialize();
	virtual void	Uninitialize();
	virtual void	Render();

private:
	GLuint	m_VAOId;
	GLuint	m_VBOId;
	Shader	m_Shader;
};

CDrawTriangles::CDrawTriangles()
{
	m_VAOId = 0;
	m_VBOId = 0;
}

CDrawTriangles::~CDrawTriangles()
{
	
}

int CDrawTriangles::Initialize()
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
		0.0f, 0.5f, 0.0f, 0.0f, 0.0, 0.8f
	};
	//������VAO
	glGenVertexArrays(1, &m_VAOId);
	glBindVertexArray(m_VAOId);
	
	//������VBO
	glGenBuffers(1, &m_VBOId);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOId);

	//����ռ䣬��������
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//ָ��������ʽ��������������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);

	//�����
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return 0;
}

void CDrawTriangles::Uninitialize()
{
	if (m_VAOId)
		glDeleteVertexArrays(1, &m_VAOId);
	if (m_VBOId)
		glDeleteBuffers(1, &m_VBOId);
}

void CDrawTriangles::Render()
{
	glBindVertexArray(m_VAOId);
	m_Shader.Use();
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
	m_Shader.UnUse();
}

static CDrawTriangles app;
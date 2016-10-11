#include"../Common/Framework.h"
#include"../Common/GL.h"
#include"../Common/Shader.h"
#include"../Common/FileLoader.h"

#pragma comment(lib, "Common.lib")
#pragma comment(lib, "Launcher.lib")
#pragma comment(lib, "SOIL.lib")

class CDraw2DTexture : public Framework
{
public:
	CDraw2DTexture();
	~CDraw2DTexture();

	virtual int		Initialize();
	virtual void	Uninitialize();
	virtual void	Render();
	virtual void	OnKeyProc(int key, int action);

private:
	GLuint			GenTexture(const char* filename, GLint internalFormat = GL_RGB,
		GLenum picFormat = GL_RGB, int loadChannels = SOIL_LOAD_RGB);

private:
	GLuint	m_VAOId;
	GLuint	m_VBOId;
	GLuint	m_EBOId;
	Shader	m_Shader;
	GLuint	m_texture0;
	GLuint	m_texture1;
	GLfloat m_MixValue;
};

CDraw2DTexture::CDraw2DTexture()
	:m_VAOId(0)
	, m_VBOId(0)
	, m_EBOId(0)
	, m_texture0(0)
	, m_texture1(0)
	, m_MixValue(0.4f)
{

}

CDraw2DTexture::~CDraw2DTexture()
{

}

int	CDraw2DTexture::Initialize()
{
	FileLoader vertexShaderFile("shader/texture2D.vertex");
	if (!vertexShaderFile.IsLoaded())
		return -1;

	FileLoader fragmentShaderFile("shader/texture2D.frag");
	if (!fragmentShaderFile.IsLoaded())
		return -1;

	if (!m_Shader.Load(vertexShaderFile.GetData(), fragmentShaderFile.GetData()))
		return -1;

	GLfloat vertices[] =
	{
		-0.5f, -0.5f, 0.0f, 0.8f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 0.8f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 0.0f, 0.0, 0.8f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	};

	GLushort indices[] =
	{
		0, 1, 2,
		0, 2, 3,
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

	//指定解析方式
	//顶点位置
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), 0);
	glEnableVertexAttribArray(0);
	//顶点颜色
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);
	//顶点纹理
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(2);

	//解除绑定
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//纹理相关
	m_texture0 = GenTexture("texture/wood.png");
	m_texture1 = GenTexture("texture/cat.png");

	return 0;
}

void CDraw2DTexture::Uninitialize()
{
	if (m_VAOId)
		glDeleteVertexArrays(1, &m_VAOId);
	if (m_VBOId)
		glDeleteBuffers(1, &m_VBOId);
	if (m_EBOId)
		glDeleteBuffers(1, &m_EBOId);
	if (m_texture0)
		glDeleteTextures(1, &m_texture0);
	if (m_texture1)
		glDeleteTextures(1, &m_texture1);
}

void CDraw2DTexture::Render()
{
	glBindVertexArray(m_VAOId);
	m_Shader.Use();
	
	//启用纹理单元，绑定纹理对象
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture0);
	glUniform1i(m_Shader.GetUniformLocation("tex1"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_texture1);
	glUniform1i(m_Shader.GetUniformLocation("tex2"), 1);

	glUniform1f(m_Shader.GetUniformLocation("mixValue"), m_MixValue);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

	glBindVertexArray(0);
	m_Shader.UnUse();
}

void CDraw2DTexture::OnKeyProc(int key, int action)
{
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		m_MixValue += 0.05f;
		if (m_MixValue > 1.0f)
			m_MixValue = 1.0f;
	}
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		m_MixValue -= 0.05f;
		if (m_MixValue < 0.0f)
			m_MixValue = 0.0f;
	}

	printf("mixValue = %.2f\n", m_MixValue);
}

GLuint CDraw2DTexture::GenTexture(const char* filename, GLint internalFormat,
	GLenum picFormat, int loadChannels )
{
	GLuint textureId = 0;

	// 创建和绑定纹理
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	// 设定wrap参数
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// 设定filter参数
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// 加载纹理
	GLubyte *pImageData = 0;
	int iPicWidth = 0, iPicHeight = 0;
	pImageData = SOIL_load_image(filename, &iPicWidth, &iPicHeight, 0, loadChannels);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, iPicWidth, iPicHeight, 0, picFormat, GL_UNSIGNED_BYTE, pImageData);
	//glGenerateMipmap(GL_TEXTURE_2D);

	//释放纹理资源
	SOIL_free_image_data(pImageData);
	glBindTexture(GL_TEXTURE_2D, 0);

	return textureId;
}

static CDraw2DTexture app;
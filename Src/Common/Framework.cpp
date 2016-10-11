#define GLEW_STATIC
#include"GL.h"
#include"Framework.h"

#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")


GLFWwindow* pMainWnd = 0;

void KeyProc(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE); // 关闭窗口
	}

	Framework::GetSingletonPtr()->OnKeyProc(key, action);
}

static Framework* sInstance = 0;

Framework::Framework()
{
	sInstance = this;
}

Framework::~Framework()
{

}

Framework* Framework::GetSingletonPtr()
{
	return sInstance;
}

int Framework::Startup()
{
	if (!glfwInit())
	{
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	pMainWnd = glfwCreateWindow(800, 600, "OpenGLSample", 0, 0);
	if (!pMainWnd)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(pMainWnd);

	glfwSetKeyCallback(pMainWnd, KeyProc);

	glewExperimental = GL_TRUE;
	GLenum status = glewInit();
	if (GLEW_OK != status)
	{
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 800, 600);

	return Initialize();
}

void Framework::Shutdown()
{
	Uninitialize();

	glfwTerminate();
}

void Framework::Loop()
{
	while (!glfwWindowShouldClose(pMainWnd))
	{
		glfwPollEvents(); // 处理例如鼠标 键盘等事件

		// 清除颜色缓冲区 重置为指定颜色
		glClearColor(0.18f, 0.04f, 0.14f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Render();

		glfwSwapBuffers(pMainWnd); // 交换缓存
	}
}
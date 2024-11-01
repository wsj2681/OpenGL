#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <cstdlib>
int main()
{
	GLFWwindow* window;
	
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	
	// glfwWindowHint(설정하고자 하는 옵션, 옵션값)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // opengl version = 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 오래된 함수들 예외처리
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // 상위 호환성 지원

	// 전체화면을 사용하려는 경우 주석해제.
	// GLFWmonitor* primary = glfwGetPrimaryMonitor();
	window = glfwCreateWindow(800, 600, "Title", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	// view port 설정
	int framebuffer_width = 0, framebuffer_height = 0;
	glfwGetFramebufferSize(window, &framebuffer_width, &framebuffer_height);
	glViewport(0, 0, framebuffer_width, framebuffer_height);


	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.6f, 0.f, 0.6f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
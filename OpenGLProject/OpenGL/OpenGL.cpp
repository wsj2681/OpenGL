#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

GLuint shader = 0;


void CreateTriangle(GLuint& VBO, GLuint& VAO);
string ReadFile(const string& filePath);
GLuint AddShader(const string& shaderCode, GLenum shaderType);
void CompileShader(const string& vsCode, const string& fsCode);
void CreateShaderProgramFromFiles(const string& vsPath, const string& fsPath);

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

	GLuint VAO; // vertex array object
	GLuint VBO; // vertex buffer object
	CreateTriangle(VBO, VAO);
	CreateShaderProgramFromFiles("shader.vert", "shader.frag");

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.6f, 0.f, 0.6f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glUseProgram(shader);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void CreateTriangle(GLuint& VBO, GLuint& VAO)
{
	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// 4번째 인자는 데이터를 어떻게 사용할 것인가에 대한 힌트이다.
	// /OpenGL/공부내용/glBufferData 사용법.txt
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

string ReadFile(const string& filePath)
{
	string content = "";
	ifstream fileStream(filePath, ios::in);

	if (!fileStream.is_open())
	{
		cout << "Failed to read " << filePath << "The file doesn't exist." << endl;
		return string();
	}

	string line = "";
	while (!fileStream.eof())
	{
		getline(fileStream, line);
		content.append(line + '\n');
	}
	fileStream.close();

	return content;
}

GLuint AddShader(const string& shaderCode, GLenum shaderType)
{
	GLuint new_shader = glCreateShader(shaderType);
	const GLchar* code[1];
	code[0] = shaderCode.c_str();

	glShaderSource(new_shader, 1, code, NULL);

	GLint result = 0;
	GLchar err_log[1024] = { 0 };

	glCompileShader(new_shader);
	glGetShaderiv(new_shader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(new_shader, sizeof(err_log), NULL, err_log);
		cout << "Error compiling the " << shaderType << "shader :" << err_log << endl;
		return 0;
	}

	return new_shader;
}

void CompileShader(const string& vsCode, const string& fsCode)
{
	GLuint vs, fs;

	shader = glCreateProgram();

	if (!shader)
	{
		cout << "Error: Cannot create shader program" << endl;
		return;
	}

	vs = AddShader(vsCode, GL_VERTEX_SHADER);
	fs = AddShader(fsCode, GL_FRAGMENT_SHADER);
	glAttachShader(shader, vs);
	glAttachShader(shader, fs);

	GLint result = 0;
	GLchar err_log[1024] = { 0 };
	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(err_log), NULL, err_log);
		cout << "Error Linking program :" << err_log << endl;
		return;
	}



}

void CreateShaderProgramFromFiles(const string& vsPath, const string& fsPath)
{
	string vsfile = ReadFile(vsPath);
	string fsfile = ReadFile(fsPath);
	CompileShader(vsfile, fsfile);
}

#pragma once
#include "stdafx.h"

class Core
{
public:
	Core();
	Core(const Core&) = delete;
	Core& operator=(const Core&) = delete;
	~Core();

private:
	GLFWwindow* window = nullptr;
	int framebuffer_width = 0;
	int framebuffer_height = 0;

	float zoomlevel = 1.f;

	GLuint shader = 0;
	GLuint VBO = 0;
	GLuint VAO = 0;
	GLuint circleVAO1 = 0;
	GLuint circleVBO1 = 0;
	GLuint circleColorVBO1 = 0;

	GLuint circleVAO2 = 0;
	GLuint circleVBO2 = 0;
	GLuint circleColorVBO2 = 0;

	vec2 position = { 0.f, 0.f };

public:

	void Init();
	void CreateTriangle();
	void CreateCircle(float radius, int segment, float z_position);

	string ReadFile(const string& filePath);
	GLuint AddShader(const string& shadercode, GLenum shadertype);
	void CompileShader(const string& vscode, const string& fscode);
	void CreateShaderProgramFromFiles(const string& vspath, const string& fspath);

	void Destory();

	void Update();

	void UpdateViewport();

	void Render();

	static void MouseCallback(GLFWwindow* window, int button, int action, int mods);
	static void MouseWheelCallback(GLFWwindow* window, double x, double y);
	void WheelUpdate(double y);

	static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};


#pragma once
#include "stdafx.h"
#include "ShaderTool.h"
#include "Triangle.h"
#include "Circle.h"
#include "Cube.h"

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

	ShaderTool* shaderTool = nullptr;
	GLuint programID = 0;

	Triangle* triangle = nullptr;
	Circle* circle = nullptr;

	Cube* cube = nullptr;

	//view values
	GLuint MatrixID = 0;
	mat4 MVP;
public:
	void Init();
	void Destory();
	void Render();
};


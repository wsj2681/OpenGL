#pragma once
#include "stdafx.h"
#include "ShaderTool.h"
#include "TextureTool.h"
#include "Triangle.h"
#include "Circle.h"
#include "Cube.h"
#include "TextureCube.h"

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
	GLuint shaderID = 0;

	TextureTool* textureTool = nullptr;
	GLuint texture = 0;
	GLuint textureID = 0;

	Triangle* triangle = nullptr;
	Circle* circle = nullptr;

	Cube* cube = nullptr;
	TextureCube* texturecube = nullptr;
	//view values
	GLuint MatrixID = 0;
	mat4 MVP;


public:
	void Init();
	void Destory();
	void Render();
};


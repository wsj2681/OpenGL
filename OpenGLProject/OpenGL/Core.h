#pragma once
#include "stdafx.h"
#include "ObjectTool.h"
#include "Input.h"
#include "Model.h"
#include "TextRender.h"


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
	TextureTool* textureTool = nullptr;
	ObjectTool* objectTool = nullptr;

	//view values
	GLuint MatrixID = 0;
	GLuint ViewMatrixID = 0;
	GLuint ModelMatrixID = 0;
	mat4 MVP;

	GLuint LightID = 0;

	Model* suzanne = nullptr;

	Input* input = nullptr;

	ShaderTool* textShader = nullptr;
	TextRender* textRender = nullptr;
	vec3 cameraPosition = vec3(0.f, 0.f, 0.f);
	vec3 cameraLookAT = vec3(0.f, 0.f, 0.f);

public:
	void Init();
	void Destory();
	void Render();
};


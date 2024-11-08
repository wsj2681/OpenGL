#pragma once
#include "stdafx.h"

class ShaderTool final
{
public:

	ShaderTool() = default;
	~ShaderTool() = default;

	GLuint LoadShaders(const char* vsPath, const char* fsPath);
	GLuint programID = 0;
};


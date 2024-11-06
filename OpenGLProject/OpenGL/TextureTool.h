#pragma once
#include "stdafx.h"
class TextureTool
{
public:
	TextureTool() = default;
	~TextureTool() = default;

	GLuint loadBMP_custom(const char* imagepath);
	GLuint LoadDDS(const char* imagepath);
};


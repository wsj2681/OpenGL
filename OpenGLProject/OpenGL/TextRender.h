#pragma once
#include "stdafx.h"
#include "ShaderTool.h"
#include <ft2build.h>
#include FT_FREETYPE_H

struct Character
{
	GLuint TextureID;
	ivec2 Size;
	ivec2 Bearing;
	GLuint Advance;
};

class TextRender
{
public:
	TextRender(const char* fontPath, int fontSize);
	~TextRender();

	void RenderText(ShaderTool& shader, const string& text, float x, float y, float scale, vec3 color);
	
private:
	map<GLchar, Character> characters;
	GLuint VAO, VBO;

	bool LoadFont(const char* fontPath, int fontSize);
};


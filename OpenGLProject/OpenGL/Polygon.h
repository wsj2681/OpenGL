#pragma once
#include "stdafx.h"

class Polygon
{
public:
	Polygon();
	Polygon(const Polygon&) = delete;
	Polygon& operator=(const Polygon&) = delete;
	~Polygon();

protected:
	//vector<GLfloat> vertices;

	GLuint VAO = 0;
	GLuint VBO = 0;
	GLuint colorVBO = 0;

public:
	GLuint getVAO();
	GLuint getVBO();
	GLuint getcolorVBO();
};

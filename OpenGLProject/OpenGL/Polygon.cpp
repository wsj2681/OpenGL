#include "Polygon.h"

Polygon::Polygon()
{
}

Polygon::~Polygon()
{
}

GLuint Polygon::getVAO()
{
	return this->VAO;
}

GLuint Polygon::getVBO()
{
	return this->VBO;
}

GLuint Polygon::getcolorVBO()
{
	return this->colorVBO;
}

#pragma once
#include "Polygon.h"
class Circle : public Polygon
{
public:
	Circle();
	~Circle();

private:

	vector<GLfloat> vertices;
	vector<GLfloat> colors;


	void Create();
};


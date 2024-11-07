#pragma once
#include "stdafx.h"
class Model
{
public:
	Model();
	Model(vector<vec3> vertices, vector<vec2> uvs, vector<vec3> normals);
	~Model();

	GLuint VAO = 0;
	GLuint VBO = 0;
	GLuint uvVBO = 0;
	GLuint normalVBO = 0;

	unsigned int vertices_count = 0;

	vector<vec3> vertices;
	vector<vec2> uvs;
	vector<vec3> normals;


	void Create();
};


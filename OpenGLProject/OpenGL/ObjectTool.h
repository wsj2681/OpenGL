#pragma once
#include "stdafx.h"

class ObjectTool
{
public:
	ObjectTool();
	~ObjectTool();

	bool loadOBJ(const char* path, vector<vec3>& out_vertices, vector<vec2>& out_uvs, vector<vec3>& out_normals);

};


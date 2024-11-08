#pragma once
#include "ShaderTool.h"
#include "TextureTool.h"
#include "ObjectTool.h"
#include "Model.h"

class ResourceManager
{
private:
	ResourceManager() = default;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	~ResourceManager();

	map<string, ShaderTool*> shaders;
	map<string, TextureTool*> textures;
	map<string, Model*> models;

public:
	static ResourceManager& getInstance()
	{
		static ResourceManager instance;
		return instance;
	}

	ShaderTool* loadShader(const string& name, const char* vsPath, const char* fsPath);
	TextureTool* loadTexture(const string& name, const char* texturePath, bool isDDS = true);
	Model* loadModel(const string& name, const char* objPath, ShaderTool* shader, TextureTool* texture);

	ShaderTool* getShader(const string& name);
	TextureTool* getTexture(const string& name);
	Model* getModel(const string& name);

	void clear();

};


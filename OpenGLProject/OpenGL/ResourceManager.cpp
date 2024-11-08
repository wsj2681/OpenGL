#include "ResourceManager.h"

ResourceManager::~ResourceManager()
{
	this->clear();
}

ShaderTool* ResourceManager::loadShader(const string& name, const char* vsPath, const char* fsPath)
{
	if (shaders.find(name) == shaders.end())
	{
		ShaderTool* shader = new ShaderTool();
		shader->LoadShaders(vsPath, fsPath);
		shaders[name] = shader;
	}
	return shaders[name];
}

TextureTool* ResourceManager::loadTexture(const string& name, const char* texturePath, bool isDDS)
{
	if (textures.find(name) == textures.end())
	{
		TextureTool* texture = new TextureTool();
		texture->LoadDDS(texturePath);
		textures[name] = texture;
	}
	return textures[name];
}

Model* ResourceManager::loadModel(const string& name, const char* objPath, ShaderTool* shader, TextureTool* texture)
{
	if (models.find(name) == models.end())
	{
		Model* model = new Model(shader, texture);
		ObjectTool objLoader;
		if (objLoader.loadOBJ(objPath, model->vertices, model->uvs, model->normals))
		{
			model->Create();
			models[name] = model;
		}
		else
		{
			delete model;
			cout << "Model : " << name << "Create Failed.\n";
			return nullptr;
		}
	}
	return models[name];
}

ShaderTool* ResourceManager::getShader(const string& name)
{
	auto it = shaders.find(name);
	return(it != shaders.end()) ? it->second : nullptr;
}

TextureTool* ResourceManager::getTexture(const string& name)
{
	auto it = textures.find(name);
	return(it != textures.end()) ? it->second : nullptr;
}

Model* ResourceManager::getModel(const string& name)
{
	auto it = models.find(name);
	return(it != models.end()) ? it->second : nullptr;
}

void ResourceManager::clear()
{
	//for (auto& pair : shaders) 
	//	delete pair.second;
	//for (auto& pair : textures) 
	//	delete pair.second;
	//for (auto& pair : models) 
	//	delete pair.second;

	shaders.clear();
	textures.clear();
	models.clear();
}



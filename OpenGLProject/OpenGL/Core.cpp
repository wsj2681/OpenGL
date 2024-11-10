#include "Core.h"
#include "ResourceManager.h"

Core::Core()
{
	Init();
}

Core::~Core()
{
	Destory();

}

void Core::Init()
{
	if (!glfwInit())
	{
		cout << "Failed to Init window" << endl;
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_SAMPLES, 4);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	this->window = glfwCreateWindow(800, 600, "Core", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(this->window);
	glfwGetFramebufferSize(window, &framebuffer_width, &framebuffer_height);

	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glClearColor(1.f, 1.f, 1.0f, 1.f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glCullFace(GL_BACK);

	input = new Input(window, framebuffer_width,framebuffer_height);
	ResourceManager& resourceManager = ResourceManager::getInstance();

	// Create ShaderTool
	shaderTool = resourceManager.loadShader("suzanne", "suzanneshader.vert", "suzanneshader.frag");

	// Create TextureTool
	textureTool = resourceManager.loadTexture("suzanne", "suzanneuvmap.DDS");
	textureTool->textureID = glGetUniformLocation(shaderTool->programID, "textureSampler");
	

	MatrixID = glGetUniformLocation(shaderTool->programID, "MVP");
	ViewMatrixID = glGetUniformLocation(shaderTool->programID, "V");
	ModelMatrixID = glGetUniformLocation(shaderTool->programID, "M");

	mat4 projection = perspective(radians(45.f), 4.f / 3.f, 0.1f, 100.f);

	mat4 view = lookAt(vec3(4.f, 3.f, 3.f), vec3(0.f, 0.f, 0.f), vec3(0.f, 1.f, 0.f));
	mat4 model = mat4(1.f);
	MVP = projection * view * model;

	// Model + OBJ file
	suzanne = resourceManager.loadModel("suzanne", "suzanne.obj", shaderTool, textureTool);

	LightID = glGetUniformLocation(shaderTool->programID, "LightPosition_worldspace");

}

void Core::Destory()
{
	if (window)
	{
		glfwDestroyWindow(window);
		window = nullptr;
	}
	glfwTerminate();

	delete input;
	delete shaderTool;
	delete textureTool;
	delete suzanne;
}

void Core::Render()
{
	while (!glfwWindowShouldClose(this->window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// ¸ðµ¨ ·»´õ¸µ
		glUseProgram(shaderTool->programID);

		input->computeMatricesFromInputs();
		mat4 view = input->getViewMatrix();
		mat4 projection = input->getProjectionMatrix();
		mat4 ModelMatrix = mat4(1.0);
		MVP = projection * view * ModelMatrix;

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &view[0][0]);

		vec3 lightPos = vec3(4.f, 4.f, 4.f);
		glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureTool->textureID);

		suzanne->Render(MVP);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

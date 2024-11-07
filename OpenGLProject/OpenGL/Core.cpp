#include "Core.h"

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

	glClearColor(0.f, 0.f, 0.4f, 0.f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glCullFace(GL_BACK);
	input = new Input(window, framebuffer_width,framebuffer_height);

	// Create ShaderTool
	shaderTool = new ShaderTool;
	//shaderID = shaderTool->LoadShaders("shader.vert", "shader.frag");
	
	shaderID = shaderTool->LoadShaders("suzanneshader.vert", "suzanneshader.frag");

	MatrixID = glGetUniformLocation(shaderID, "MVP");
	ViewMatrixID = glGetUniformLocation(shaderID, "V");
	ModelMatrixID = glGetUniformLocation(shaderID, "M");

	mat4 projection = perspective(radians(45.f), 4.f / 3.f, 0.1f, 100.f);

	mat4 view = lookAt(
		vec3(4.f, 3.f, 3.f),
		vec3(0.f, 0.f, 0.f),
		vec3(0.f, 1.f, 0.f)
	);
	mat4 model = mat4(1.f);
	MVP = projection * view * model;

	textureTool = new TextureTool;
	texture = textureTool->LoadDDS("suzanneuvmap.DDS");
	textureID = glGetUniformLocation(shaderID, "textureSampler");

	// Create Object
	//triangle = new Triangle;
	//circle = new Circle;
	// cube = new Cube;

	//texturecube = new TextureCube;


	// Model + OBJ file
	cubemodel = new Model;
	objectTool = new ObjectTool;
	objectTool->loadOBJ("cube.obj",cubemodel->vertices, cubemodel->uvs, cubemodel->normals);
	cubemodel->Create();

	suzanne = new Model;
	objectTool->loadOBJ("suzanne.obj", suzanne->vertices, suzanne->uvs, suzanne->normals);
	suzanne->Create();

	LightID = glGetUniformLocation(shaderID, "LightPosition_worldspace");

}

void Core::Destory()
{
	if (window)
	{
		glfwDestroyWindow(window);
		window = nullptr;
	}
	glfwTerminate();
}

void Core::Render()
{
	while (!glfwWindowShouldClose(this->window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shaderID);

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

		// draw triangle
		//glBindVertexArray(triangle->getVAO());
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		// draw circle
		//glBindVertexArray(circle->getVAO());
		//glDrawArrays(GL_TRIANGLE_FAN, 0, 36);

		// draw cube
		//glBindVertexArray(cube->getVAO());
		//glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

		// draw texture cube
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(textureID, 0);
		glBindVertexArray(suzanne->VAO);
		glDrawArrays(GL_TRIANGLES, 0, suzanne->vertices.size());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

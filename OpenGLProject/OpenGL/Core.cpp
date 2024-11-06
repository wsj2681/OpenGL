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
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glDepthFunc(GL_LEQUAL);
	//glDepthFunc(GL_LESS);

	// Create ShaderTool
	shaderTool = new ShaderTool;
	//shaderID = shaderTool->LoadShaders("shader.vert", "shader.frag");
	
	shaderID = shaderTool->LoadShaders("textureshader.vert", "textureshader.frag");

	MatrixID = glGetUniformLocation(shaderID, "MVP");
	mat4 projection = perspective(radians(45.f), 4.f / 3.f, 0.1f, 100.f);

	mat4 view = lookAt(
		vec3(4.f, 3.f, 3.f),
		vec3(0.f, 0.f, 0.f),
		vec3(0.f, 1.f, 0.f)
	);
	mat4 model = mat4(1.f);
	MVP = projection * view * model;

	textureTool = new TextureTool;
	texture = textureTool->LoadDDS("uvtemplate.DDS");
	textureID = glGetUniformLocation(shaderID, "textureSampler");

	// Create Object
	//triangle = new Triangle;
	//circle = new Circle;
	// cube = new Cube;

	texturecube = new TextureCube;
}

void Core::Destory()
{
	glfwTerminate();
}

void Core::Render()
{
	while (!glfwWindowShouldClose(this->window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shaderID);

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

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
		glBindVertexArray(texturecube->getVAO());
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

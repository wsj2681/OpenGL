#include "Core.h"

Core::Core()
{
	this->Init();
}

Core::~Core()
{
}

void Core::Init()
{
	if (!glfwInit())
	{
		cout << "Failed to Init window" << endl;
		exit(EXIT_FAILURE);
	}

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
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, KeyboardCallback);
	glfwSetMouseButtonCallback(window, MouseCallback);
	glfwSetScrollCallback(window, MouseWheelCallback);

	glfwGetFramebufferSize(window, &framebuffer_width, &framebuffer_height);
	glViewport(0, 0, framebuffer_width, framebuffer_height);

	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//CreateTriangle();
	CreateCircle(0.5f, 36);
	CreateShaderProgramFromFiles("shader.vert", "shader.frag");


}

void Core::CreateTriangle()
{
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Core::CreateCircle(float radius, int segment)
{
	vector<float> vertices1;
	vector<float> colors1;
	for (int i = 0; i < segment; ++i)
	{
		float angle = 2.f * M_PI * float(i) / float(segment);
		float x = radius * cos(angle) - 0.5f;
		float y = radius * sin(angle);

		vertices1.push_back(x);
		vertices1.push_back(y);
		vertices1.push_back(0.0f);

		float r = (sin(angle + 0.0f) * 0.5f + 0.5f);
		float g = (sin(angle + 2.0f * M_PI / 3.0f) * 0.5f + 0.5f);
		float b = (sin(angle + 4.0f * M_PI / 3.0f) * 0.5f + 0.5f);
		colors1.push_back(r);
		colors1.push_back(g);
		colors1.push_back(b);
	}
	vector<float> vertices2;
	vector<float> colors2;

	for (int i = 0; i < segment; ++i)
	{
		float angle = 2.f * M_PI * float(i) / float(segment);
		float x = radius * cos(angle) + 0.5f;
		float y = radius * sin(angle);

		vertices2.push_back(x);
		vertices2.push_back(y);
		vertices2.push_back(0.0f);

		float r = (sin(angle + 0.0f) * 0.5f + 0.5f);
		float g = (sin(angle + 2.0f * M_PI / 3.0f) * 0.5f + 0.5f);
		float b = (sin(angle + 4.0f * M_PI / 3.0f) * 0.5f + 0.5f);
		colors2.push_back(r);
		colors2.push_back(g);
		colors2.push_back(b);
	}
	glGenVertexArrays(1, &circleVAO1);
	glBindVertexArray(circleVAO1);

	glGenBuffers(1, &circleVBO1);
	glBindBuffer(GL_ARRAY_BUFFER, circleVBO1);
	glBufferData(GL_ARRAY_BUFFER, vertices1.size() * sizeof(float), vertices1.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &circleColorVBO1);
	glBindBuffer(GL_ARRAY_BUFFER, circleColorVBO1);
	glBufferData(GL_ARRAY_BUFFER, colors1.size() * sizeof(float), colors1.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(1);


	glGenVertexArrays(1, &circleVAO2);
	glBindVertexArray(circleVAO2);

	glGenBuffers(1, &circleVBO2);
	glBindBuffer(GL_ARRAY_BUFFER, circleVBO2);
	glBufferData(GL_ARRAY_BUFFER, vertices2.size() * sizeof(float), vertices2.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &circleColorVBO2);
	glBindBuffer(GL_ARRAY_BUFFER, circleColorVBO2);
	glBufferData(GL_ARRAY_BUFFER, colors2.size() * sizeof(float), colors2.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

string Core::ReadFile(const string& filePath)
{
	string content = "";
	ifstream fileStream(filePath, ios::in);

	if (!fileStream.is_open())
	{
		cout << "Failed to read " << filePath << "The file doesn't exist." << endl;
		return string();
	}

	string line = "";
	while (!fileStream.eof())
	{
		getline(fileStream, line);
		content.append(line + '\n');
	}
	fileStream.close();

	return content;
}

GLuint Core::AddShader(const string& shadercode, GLenum shadertype)
{
	GLuint new_shader = glCreateShader(shadertype);
	const GLchar* code[1];
	code[0] = shadercode.c_str();

	glShaderSource(new_shader, 1, code, NULL);

	GLint result = 0;
	GLchar err_log[1024] = { 0 };

	glCompileShader(new_shader);
	glGetShaderiv(new_shader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(new_shader, sizeof(err_log), NULL, err_log);
		cout << "Error compiling the " << shadertype << "shader :" << err_log << endl;
		return 0;
	}

	return new_shader;
}

void Core::CompileShader(const string& vscode, const string& fscode)
{
	GLuint vs, fs;

	shader = glCreateProgram();

	if (!shader)
	{
		cout << "Error: Cannot create shader program" << endl;
		return;
	}

	vs = AddShader(vscode, GL_VERTEX_SHADER);
	fs = AddShader(fscode, GL_FRAGMENT_SHADER);
	glAttachShader(shader, vs);
	glAttachShader(shader, fs);

	GLint result = 0;
	GLchar err_log[1024] = { 0 };
	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(err_log), NULL, err_log);
		cout << "Error Linking program :" << err_log << endl;
		return;
	}
}

void Core::CreateShaderProgramFromFiles(const string& vspath, const string& fspath)
{
	string vsfile = ReadFile(vspath);
	string fsfile = ReadFile(fspath);
	CompileShader(vsfile, fsfile);
}

void Core::Destory()
{
	glfwTerminate();
}

void Core::Update()
{
	glfwPollEvents();
}

void Core::UpdateViewport()
{
	int width = 0, height = 0;
	glfwGetFramebufferSize(window, &width, &height);
	int newWidth = static_cast<int>(width / zoomlevel);
	int newHeight = static_cast<int>(height / zoomlevel);

	glViewport((width - newWidth) / 2, (height - newHeight) / 2, newWidth, newHeight);

}

void Core::Render()
{
	while (!glfwWindowShouldClose(this->window))
	{
		glClearColor(1.f, 1.f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glUseProgram(shader);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//glBindVertexArray(0);


		mat4 model = glm::translate(mat4(1.f), vec3(position.x, position.y, 0.f));
		GLuint modelLoc = glGetUniformLocation(shader, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glBindVertexArray(circleVAO1);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 36);
		glBindVertexArray(0);



		mat4 model2 = glm::translate(mat4(1.f), vec3(0.f, 0.f, 0.f));
		GLuint modelLoc2 = glGetUniformLocation(shader, "model");
		glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, glm::value_ptr(model2));


		glBindVertexArray(circleVAO2);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 36);
		glBindVertexArray(0);

		glfwSwapBuffers(this->window);
		this->Update();
	}
}

void Core::MouseCallback(GLFWwindow* window, int button, int action, int mods)
{
	Core* otherwindow = static_cast<Core*>(glfwGetWindowUserPointer(window));
	double x, y;
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
	
		glfwGetCursorPos(window, &x, &y);
		cout << "x : " << x << " y : " << y << endl;
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		cout << "right mouse press" << endl;
	}
	else if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
	{
		otherwindow->zoomlevel = 1.f;
		otherwindow->UpdateViewport();
	}
}

void Core::MouseWheelCallback(GLFWwindow* window, double x, double y)
{
	Core* otherwindow = static_cast<Core*>(glfwGetWindowUserPointer(window));
	if (otherwindow)
	{
		otherwindow->WheelUpdate(y);
	}
}

void Core::WheelUpdate(double y)
{
	zoomlevel += static_cast<float>(y) * 0.1f;
	if (zoomlevel < 0.5f)
	{
		zoomlevel = 0.5f;
	}
	else if (zoomlevel > 4.f)
	{
		zoomlevel = 4.f;
	}
	UpdateViewport();
}

void Core::KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Core* otherwindow = static_cast<Core*>(glfwGetWindowUserPointer(window));
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_W)
		{
			otherwindow->position.y += 0.1f;
		}
		else if (key == GLFW_KEY_S)
		{
			otherwindow->position.y -= 0.1f;
		}
		else if (key == GLFW_KEY_A)
		{
			otherwindow->position.x -= 0.1f;
		}
		else if (key == GLFW_KEY_D)
		{
			otherwindow->position.x += 0.1f;
		}
	}
}

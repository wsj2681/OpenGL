#include "Circle.h"

Circle::Circle()
{
	Create();
}

Circle::~Circle()
{

}

void Circle::Create()
{
	float radius = 0.5f;
	int segment = 36;
	float z_position = 1.f;

	for (int i = 0; i < segment; ++i)
	{
		float angle = 2.f * M_PI * float(i) / float(segment);
		float x = radius * cos(angle) - 0.5f;
		float y = radius * sin(angle);

		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(z_position);

		float r = (sin(angle + 0.0f) * 0.5f + 0.5f);
		float g = (sin(angle + 2.0f * M_PI / 3.0f) * 0.5f + 0.5f);
		float b = (sin(angle + 4.0f * M_PI / 3.0f) * 0.5f + 0.5f);
		colors.push_back(r);
		colors.push_back(g);
		colors.push_back(b);
	}

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &colorVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(float), colors.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

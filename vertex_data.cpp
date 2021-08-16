#include "vertex_data.h"


VertexData::VertexData(float* verticies, int length, int width)
{
	size = length / width;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * length, verticies, GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, width, GL_FLOAT, GL_FALSE, width * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

VertexData::~VertexData()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void VertexData::Draw(unsigned int mode)
{
	glBindVertexArray(VAO);
	glDrawArrays(mode, 0, size);
	glBindVertexArray(0);
}

void VertexData::Draw(unsigned int mode, unsigned int verticies)
{
	if (verticies > size)
		verticies = size;
	glBindVertexArray(VAO);
	glDrawArrays(mode, 0, verticies);
	glBindVertexArray(0);
}
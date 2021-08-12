#ifndef VERTEX_DATA_H
#define VERTEX_DATA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class VertexData
{
public:
	VertexData(float* verticies, int length, int width);
	~VertexData();

	void Draw(unsigned int mode);
	void Draw(unsigned int mode, unsigned int verticies);

private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int size;
};



#endif
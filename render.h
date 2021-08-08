#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "texture.h"
#include "geometry.h"

class Renderer
{
public:
	Renderer(Shader &spriteShader);
	~Renderer();

	void DrawTex(Texture& texture, glm::vec2 position, glm::vec2 size, float rotate = 0.0f, glm::vec3 colour = glm::vec3(1.0f));
	void DrawSquare(glm::vec2 position, glm::vec2 size, float rotate = 0.0f, glm::vec3 colour = glm::vec3(1.0f));
	void DrawLine(glm::vec2 point1, glm::vec2 point2, glm::vec3 colour, float width);

private:
	Shader shader;
	unsigned int quadVAO, quadVBO, lineVAO, lineVBO;
	void initRenderData();
};

#endif
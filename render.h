#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "vertex_data.h"
#include "shader.h"
#include "texture.h"
#include "geometry.h"
#include "text.h"

class Renderer
{
public:
	Renderer(int width, int height);
	~Renderer();

	void DrawTex(Texture& texture, glm::vec2 position, glm::vec2 size, float rotate = 0.0f, glm::vec3 colour = glm::vec3(1.0f));
	void DrawString(std::string text, glm::vec2 position, float size, float rotate = 0.0f, glm::vec3 colour = glm::vec3(1.0f));
	void DrawSquare(glm::vec2 position, glm::vec2 size, float rotate = 0.0f, glm::vec3 colour = glm::vec3(1.0f));
	void DrawLine(glm::vec2 point1, glm::vec2 point2, glm::vec3 colour, float width);
	void DrawPoint(glm::vec2 point, glm::vec3 colour, float size);
	void Resize(int width, int height);
private:
	Shader* _textureShader;
	Font* CourierNew;
	VertexData* _quad;
	VertexData* _line;
	void initRenderData();
	void initFontData();
	glm::mat4 getModel(glm::vec2 position, glm::vec2 size, float rotate);
};

#endif
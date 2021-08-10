#pragma once
#ifndef APP_H
#define APP_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <filesystem>

#include "render.h"
#include "shader.h"
#include "graph.h"
#include "texture.h"
#include "csv.h"

#include "tinyfiledialogs.h"

class App
{
public:
	bool keys[1024];
	bool buttons[8];
	Vector2 mousePos;
	unsigned int Width, Height;

	App(unsigned int width, unsigned int height);
	~App();

	void Init();
	void Update(float dt);
	void Render();
	void Resize(int width, int height);
	void Scroll(double offset);
private:
	Renderer *renderer;
	glm::vec2 cameraOffset = glm::vec2(0.0f);
	Graph* graph;
};



#endif
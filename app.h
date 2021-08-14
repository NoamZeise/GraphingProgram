#pragma once
#ifndef APP_H
#define APP_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <filesystem>

#include "render.h"
#include "graph.h"
#include "ui_manager.h"
#include "input.h"



class App
{
public:
	App(unsigned int width, unsigned int height);
	~App();

	void Init();
	void Update(float dt);
	void Render();
	void Resize(int width, int height);
	void Scroll(double offset);
	void ProcessKeyboard(int key, bool pressed);
	void ProcessMouseBtn(int key, bool pressed);
	void ProcessMouse(double xPos, double yPos);
	bool ShouldClose();

private:
	unsigned int Width, Height;
	Renderer* renderer;
	glm::vec2 cameraOffset = glm::vec2(0.0f);
	Graph* graph;
	bool shouldClose = false;
	UIManager* uiManager;
	Input input;
};



#endif
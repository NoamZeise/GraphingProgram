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
#include "csv.h"
#include "menu.h"

#include "tinyfiledialogs.h"


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
	glm::vec2 mousePos = glm::vec2(0);
	Renderer* renderer;
	glm::vec2 cameraOffset = glm::vec2(0.0f);
	Graph* graph;
	std::vector<Csv*> openCsvs;
	bool dialogOpened = false;
	bool keys[1024];
	bool buttons[8];
	bool shouldClose = false;

	Menu* topMenu;
	struct menuButtons
	{
		std::string importCsv = "Import CSV";
		std::string addFunction = "Polynomial";
		std::string exit = "Exit";
	};
	menuButtons btnNames;


	void MenuControls();
};



#endif
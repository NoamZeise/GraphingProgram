#pragma once
#ifndef UI_MANAGER
#define UI_MANAGER

#include <string>
#include <vector>
#include <filesystem>

#include "geometry.h"
#include "menu.h"
#include "dropMenu.h"
#include "button.h"
#include "render.h"
#include "graph.h"
#include "csv.h"
#include "input.h"
#include "options.h"

#include "tinyfiledialogs.h"

class UIManager
{
public:
	UIManager(int width, int height);
	~UIManager();

	bool Update(Graph* graph, Input* input);
	void Render(Renderer* renderer);

	void Resize(int width, int height);
	bool Paused() { return paused; }
private:
	struct menuButtons
	{
		std::string importCsv = "Import CSV";
		std::string addFunction = "Polynomial";
		std::string clearGraph = "Clear";
		std::string exit = "Exit";
	};
	menuButtons btnNames;
	Menu* topMenu;
	DropMenu* importMenu;
	std::vector<Base*> menus;
	std::vector<Csv*> openCsvs;
	std::vector<Graphic*> graphics;
	Options* option = nullptr;
	bool paused = false;
	int width;
	int height;
};


#endif
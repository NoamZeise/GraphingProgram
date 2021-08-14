#pragma once
#ifndef DROP_MENU_H
#define DROP_MENU_H


#include <string>
#include <vector>

#include "geometry.h"
#include "base.h"
#include "button.h"
#include "render.h"
#include "menu.h"

class DropMenu : public Base
{
public:
	DropMenu(std::string text, bool horizontal, Button* button);
	void Render(Renderer* renderer);
	void Update(double xPos, double yPos, bool pressed);
	void Resize();

	Menu DMenu;

private:
	bool horizontal;
	bool dropped = false;
	Button* button;

};


#endif
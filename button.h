#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <glm/glm.hpp>
#include "geometry.h"
#include "render.h"
#include "base.h"

class Button : public Base
{
public:
	Button(Vector2 pos, Vector2 size, std::string text);
	void Render(Renderer* renderer);
	void Update(double xPos, double yPos, bool pressed);
	bool Pressed();
	bool Hovering();
protected:
	std::string text;
	bool hover = false;
	bool justPressed = false;
	bool unclickedHover = false;
};




#endif
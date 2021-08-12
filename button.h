#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

#include "render.h"

typedef void(*callbackFunc)();

class Button
{
public:
	Button(glm::vec2 pos, glm::vec2 size, std::string text);
	void Render(Renderer* renderer);
	void Mouse(double xPos, double yPos, bool pressed);
	void Resize(glm::vec2 pos, glm::vec2 size);
	bool pressed();
private:
	glm::vec2 _pos;
	glm::vec2 _size;
	std::string _text;
	bool hover = false;
	bool justPressed = false;
	bool unclickedHover = false;
};




#endif
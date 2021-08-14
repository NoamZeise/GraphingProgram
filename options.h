#pragma once
#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>
#include <glm/glm.hpp>

#include "render.h"
#include "input.h"

class Options
{
public:
	Options(std::string parent, std::string text, int width, int height);
	std::string Update(Input* input);
	void Render(Renderer* renderer);
	void Resize(int width, int height);
	std::string Parent() { return parent; }
private:
	std::string inputText = "";
	std::string parent;
	std::string text;
	Input prevInput;

	glm::vec2 position = glm::vec2(0);
	glm::vec2 size = glm::vec2(0);
};

#endif
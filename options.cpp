#include "options.h"
#include <iostream>
Options::Options(std::string parent, std::string text, int width, int height)
{
	this->parent = parent;
	this->text = text;
	Resize(width, height);
}

std::string Options::Update(Input* input)
{
	for (unsigned int i = 0; i < 9; i++)
	{
		if (input->Keys[GLFW_KEY_0 + i] && !prevInput.Keys[GLFW_KEY_0 + i])
		{
			inputText.append(std::to_string(i));
		}
	}
	if (input->Keys[GLFW_KEY_COMMA] && !prevInput.Keys[GLFW_KEY_COMMA])
	{
		inputText.append(",");
	}
	if (input->Keys[GLFW_KEY_PERIOD] && !prevInput.Keys[GLFW_KEY_PERIOD])
	{
		inputText.append(".");
	}

	if (input->Keys[GLFW_KEY_BACKSPACE] && !prevInput.Keys[GLFW_KEY_BACKSPACE])
	{
		if (inputText.size() != 0)
		{
			inputText = inputText.substr(0, inputText.size() - 1);
		}
	}

	if (input->Keys[GLFW_KEY_ENTER])
	{
		if (inputText == "")
			return "'";
		return inputText;
	}
	prevInput = *input;
	return "";
}

void Options::Render(Renderer* renderer)
{

	renderer->DrawSquare(position, size, 0, glm::vec3(1));

	renderer->DrawString(text, 
		glm::vec2(position.x + (size.x * 0.05),
			(position.y + (size.y)) - (size.y * 0.7)),
		size.x / 25, 0, glm::vec3(0));


	glm::vec2 bpos = glm::vec2(position.x + (size.x * 0.01), (position.y + (size.y)) - (size.x / 10));
	glm::vec2 bsize = glm::vec2(size.x * 0.98, size.y / 10);
	renderer->DrawSquare(
		bpos,
		bsize,
		0, glm::vec3(0));

	renderer->DrawString(inputText, 
		glm::vec2(bpos.x + (bsize.x * 0.1),
			(bpos.y + (bsize.y)) - (bsize.y * 0.2)),
		bsize.y * 0.8, 0, glm::vec3(1));
}

void Options::Resize(int width, int height)
{
	this->position = glm::vec2(width / 10, height / 10);
	this->size = glm::vec2(width / 2, height / 2);
	
}
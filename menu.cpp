#include "menu.h"


Menu::Menu(glm::vec2 position, glm::vec2 size, bool horizontal)
{
	this->position = position;
	this->size = size;
	this->horizontal = horizontal;
}

Menu::~Menu()
{
	std::map<std::string, Button*>::iterator it;
	for (it = buttons.begin(); it != buttons.end(); it++)
	{
		delete it->second;
	}
}

void Menu::Update(double xPos, double yPos, bool pressed)
{
	std::map<std::string, Button*>::iterator it;
	for (it = buttons.begin(); it != buttons.end(); it++)
	{
		it->second->Mouse(xPos, yPos, pressed);
	}
}

void Menu::Render(Renderer* renderer)
{
	std::map<std::string, Button*>::iterator it;
	for (it = buttons.begin(); it != buttons.end(); it++)
	{
		it->second->Render(renderer);
	}
}

void Menu::AddButton(std::string text)
{
	btnOrder.push_back(text);
	glm::vec2 pos(0);
	if (horizontal)
		pos = glm::vec2(position.x + (size.x * buttonsCount), position.y);
	else
		pos = glm::vec2(position.x, position.y + (size.y * buttonsCount));

	Button* btn = new Button(pos, size, text);
	buttons.insert(std::pair<std::string, Button*>(text, btn));

	buttonsCount++;
}

bool Menu::WasClicked(std::string buttonName)
{
	if (buttons.count(buttonName))
	{
		return buttons[buttonName]->pressed();
	}
	return false;
}

void Menu::Resize(glm::vec2 pos, glm::vec2 size)
{
	this->position = pos;
	this->size = size;
	for (unsigned int i = 0; i < btnOrder.size(); i++)
	{
		glm::vec2 pos(0);
		if (horizontal)
			pos = glm::vec2(position.x + (size.x * i), position.y);
		else
			pos = glm::vec2(position.x, position.y + (size.y * i));

		buttons[btnOrder.at(i)]->Resize(pos, size);
	}
}
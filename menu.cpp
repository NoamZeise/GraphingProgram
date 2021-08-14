#include "menu.h"


Menu::Menu(Vector2 position, Vector2 size, bool horizontal) : Base(position, size)
{
	this->horizontal = horizontal;
}

Menu::~Menu()
{
	for (std::map<std::string, Button*>::iterator it = buttons.begin(); it != buttons.end(); it++)
	{
		delete it->second;
	}
}

void Menu::Update(double xPos, double yPos, bool pressed)
{
	for (std::map<std::string, Button*>::iterator it = buttons.begin(); it != buttons.end(); it++)
	{
		it->second->Update(xPos, yPos, pressed);
	}
}

void Menu::Render(Renderer* renderer)
{
	for (std::map<std::string, Button*>::iterator it = buttons.begin(); it != buttons.end(); it++)
	{
		it->second->Render(renderer);
	}
}

Button* Menu::AddButton(std::string text)
{
	btnOrder.push_back(text);
	Vector2 pos(0, 0);
	if (horizontal)
		pos = Vector2(_Position.x + (_Size.x * buttonsCount), _Position.y);
	else
		pos = Vector2(_Position.x, _Position.y + (_Size.y * buttonsCount));

	Button* btn = new Button(pos, _Size, text);
	buttons.insert(std::pair<std::string, Button*>(text, btn));
	buttonsCount++;
	return btn;
}

bool Menu::WasClicked(std::string buttonName)
{
	if (buttons.count(buttonName))
	{
		return buttons[buttonName]->Pressed();
	}
	return false;
}

void Menu::Resize(Vector2 pos, Vector2 size)
{
	this->_Position = pos;
	this->_Size = size;
	realignButtons();
}

void Menu::realignButtons()
{
	for (unsigned int i = 0; i < btnOrder.size(); i++)
	{
		Vector2 pos(0, 0);
		if (horizontal)
			pos = Vector2(_Position.x + (this->_Size.x * i), _Position.y);
		else
			pos = Vector2(_Position.x, _Position.y + (this->_Size.y * i));

		buttons[btnOrder.at(i)]->Resize(pos, this->_Size);
	}
}

void Menu::Remove(std::string text)
{
	for (unsigned int i = 0; i < btnOrder.size(); i++)
	{
		if (btnOrder[i] == text)
		{
			btnOrder.erase(btnOrder.begin() + i);
			break;
		}
	}

	delete buttons[text];
	buttons.erase(text);
	buttonsCount--;

	realignButtons();
}

bool Menu::Hovering()
{
	for (std::map<std::string, Button*>::iterator it = buttons.begin(); it != buttons.end(); it++)
		if (it->second->Hovering())
			return true;
	return false;
}


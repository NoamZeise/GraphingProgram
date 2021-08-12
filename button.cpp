#include "button.h"


Button::Button(glm::vec2 pos, glm::vec2 size, std::string text)
{
	_pos = pos;
	_size = size;
	_text = text;
}

void Button::Render(Renderer* renderer)
{
	renderer->DrawSquare(_pos, _size, 0, glm::vec3(0.0f));

	if(hover)
		renderer->DrawSquare(_pos, glm::vec2(_size.x * 0.98f, _size.y * 0.9f), 0, glm::vec3(0.7f));
	else
		renderer->DrawSquare(_pos, glm::vec2(_size.x * 0.98f, _size.y * 0.9f), 0, glm::vec3(1.0f));

	renderer->DrawString(_text, glm::vec2(_pos.x + _size.y * 0.3f, _pos.y + _size.y - _size.y * 0.3f), _size.y * 0.8f, 0, glm::vec3(0.0f));
}

void Button::Mouse(double xPos, double yPos, bool clicked)
{
	hover =
		(xPos > _pos.x && xPos < (double)_pos.x + (double)_size.x && yPos > _pos.y && yPos < (double)_pos.y + (double)_size.y);

	if (clicked && !justPressed && hover && unclickedHover)
	{
		justPressed = true;
	}
	else if (!clicked)
		justPressed = false;

	if (!clicked && hover)
		unclickedHover = true;

	if (!hover)
		unclickedHover = false;
}

bool Button::pressed()
{
	if (justPressed)
	{
		hover = false;
		unclickedHover = false;
		justPressed = false;
		return true;
	}
	return justPressed;
}


void Button::Resize(glm::vec2 pos, glm::vec2 size)
{
	this->_pos = pos;
	this->_size = size;
}


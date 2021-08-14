#include "button.h"


Button::Button(Vector2 pos, Vector2 size, std::string text) : Base(pos, size)
{
	this->text = text;
}

void Button::Render(Renderer* renderer)
{
	renderer->DrawSquare(glm::vec2(_Position.x, _Position.y), glm::vec2(_Size.x, _Size.y), 0, glm::vec3(0.0f));

	if(hover)
		renderer->DrawSquare(glm::vec2(_Position.x, _Position.y), glm::vec2(_Size.x * 0.98f, _Size.y * 0.9f), 0, glm::vec3(0.7f));
	else
		renderer->DrawSquare(glm::vec2(_Position.x, _Position.y), glm::vec2(_Size.x * 0.98f, _Size.y * 0.9f), 0, glm::vec3(1.0f));

	renderer->DrawString(text,
		glm::vec2(_Position.x + _Size.y * 0.3f,
			_Position.y + _Size.y - _Size.y * 0.3f),
		_Size.y * 0.8f, 0, glm::vec3(0.0f));
}

void Button::Update(double xPos, double yPos, bool clicked)
{
	hover =
		(xPos >= _Position.x &&
			xPos <= (double)_Position.x + (double)_Size.x &&
			yPos >= _Position.y &&
			yPos <= (double)_Position.y + (double)_Size.y);

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

bool Button::Pressed()
{
	if (justPressed)
	{
		unclickedHover = false;
		justPressed = false;
		return true;
	}
	return justPressed;
}

bool Button::Hovering()
{
	return hover;
}


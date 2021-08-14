#include "dropMenu.h"


DropMenu::DropMenu(std::string text, bool horizontal, Button* button) : Base(Vector2(0, 0), Vector2(0, 0))
{
	this->button = button;
	this->horizontal = horizontal;
	DMenu = Menu(button->getPosition(), button->getSize(), false);
	Resize();
}

void DropMenu::Render(Renderer* renderer)
{
	if(dropped)
		DMenu.Render(renderer);
}
void DropMenu::Update(double xPos, double yPos, bool pressed)
{

	if (button->Hovering() || (DMenu.Hovering()))
		dropped = true;
	else
		dropped = false;

	if(dropped)
		DMenu.Update(xPos, yPos, pressed);
}

void DropMenu::Resize()
{
	if(horizontal)
		DMenu.Resize(Vector2(button->getPosition().x + button->getSize().x, button->getPosition().y), button->getSize());
	else
		DMenu.Resize(Vector2(button->getPosition().x, button->getPosition().y + button->getSize().y), button->getSize());
		
}


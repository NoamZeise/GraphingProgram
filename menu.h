#ifndef MENU_H
#define MENU_H

#include <map>
#include <string>
#include <vector>

#include "button.h"
#include "render.h"

class Menu
{
public:
	Menu(glm::vec2 pos, glm::vec2 size, bool horizontal);
	~Menu();
	void Update(double xPos, double yPos, bool pressed);
	void Render(Renderer* renderer);
	void AddButton(std::string text);
	bool WasClicked(std::string text);
	void Resize(glm::vec2 pos, glm::vec2 size);

private:
	glm::vec2 position;
	glm::vec2 size;
	bool horizontal;
	std::vector<std::string> btnOrder;
	std::map<std::string, Button*> buttons;
	int buttonsCount = 0;
};


#endif
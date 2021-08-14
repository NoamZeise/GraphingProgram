#ifndef MENU_H
#define MENU_H


#include <map>
#include <string>
#include <vector>

#include "geometry.h"
#include "base.h"
#include "button.h"
#include "render.h"

class Menu : public Base
{
public:
	Menu(Vector2 pos, Vector2 size, bool horizontal);
	Menu() {}
	~Menu();
	void Update(double xPos, double yPos, bool pressed);
	void Render(Renderer* renderer);
	Button* AddButton(std::string text);
	//void AddDropMenu(std::string text, bool horizontal);

	bool WasClicked(std::string text);
	void Resize(Vector2 pos, Vector2 size);
	void Remove(std::string text);
	bool Hovering();


private:
	bool horizontal = false;
	std::vector<std::string> btnOrder;
	std::map<std::string, Button*> buttons;
	int buttonsCount = 0;

	void realignButtons();
};


#endif
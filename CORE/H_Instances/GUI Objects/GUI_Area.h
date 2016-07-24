#pragma once
#include "Control.h"
#include "VisibleElement.h"
#include "SDL.h"

class GUI_Area : public Control
{
public:
	GUI_Area(int x, int y, int w, int h);
	GUI_Area(pugi::xml_node node);
	GUI_Area(GUI_Area& other);

	virtual void update();
	virtual void handleInput(int keyCode, int upDown = 0, int x = 0, int y = 0);
	virtual void draw(SDL_Renderer* renderer);

	void add(Control* control, int x, int y);
	void add(VisibleElement* element, int x, int y);
	virtual void move(int x, int y, bool relative = true);
private:
	std::vector<Control*> controls;

	virtual void mouseEnter();
	virtual void mouseLeave();
	virtual void mouseDown();
	virtual void mouseUp();
};
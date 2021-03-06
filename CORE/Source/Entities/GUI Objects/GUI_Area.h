#pragma once
#include "Control.h"
#include "VisibleElement.h"
#include "SDL.h"

class GUI_Area : public Control
{
public:
	GUI_Area();
	GUI_Area(GUI_Area& other);

	virtual void get_data(DataSource* source);

	virtual void update();
	virtual void draw(SDL_Renderer* renderer);
   virtual void handle(Event e);


	/*void add(Control* control, int x, int y);
	void add(VisibleElement* element, int x, int y);*/
private:
	std::vector<Control*> controls;

	virtual void mouseEnter();
	virtual void mouseLeave();
	virtual void mouseDown();
	virtual void mouseUp();
};
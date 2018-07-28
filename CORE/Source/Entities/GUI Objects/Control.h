#pragma once
#include "Entity.h"
#include "SDL.h"
#include "VisibleElement.h"

class MenuScreen;

class Control : public Entity
{
public:
	Control();

	void Control::get_data(DataSource* source);

   virtual void handle(Event e);

	//Enable or disable the control for drawing
	void show();
	void hide();

protected:
	bool isWithin(int x, int y);

	std::vector<VisibleElement*> elements;

	bool mouseHovering;
	bool mouseIsDown;

	bool cancelInputOnMouseLeave = false;

	bool hidden;

	DataImpl<int>* w;
	DataImpl<int>* h;
	DataImpl<int>* x;
	DataImpl<int>* y;
};
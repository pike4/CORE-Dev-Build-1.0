#pragma once
#include "Entity.h"
#include "SDL.h"
#include "VisibleElement.h"

class MenuScreen;

class Control : public Entity
{
public:
	SimpleData<int>* w;
	SimpleData<int>* h;

	DataOffset<int>* x;
	DataOffset<int>* y;

	Control();
	Control(Definer* definer, MenuScreen* parent);
	Control(Definer* definer);

	Control(int x, int y, int w, int h);

	void registerSelf(Entity* parent);

	virtual void handleInput(int keyCode, int upDown = 0, int x = 0, int y = 0);

	void move(int aX, int aY);

	//Enable or disable the control for drawing
	void show();
	void hide();

protected:
	bool isWithin(int x, int y);

	void getArgsFromNode(Definer* definer);

	std::vector<VisibleElement*> elements;

	bool mouseHovering;
	bool mouseIsDown;

	bool cancelInputOnMouseLeave = false;

	bool hidden;
};
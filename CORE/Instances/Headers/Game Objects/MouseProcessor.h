#pragma once
#include "Component.h"
#include "Timer.h"
#include "Control.h"

//Component that handles basic mouse events and checks to see if more advanced mouse events like
//double-click, mouse enter, drag, etc. have occured
class MouseProcessor : public Component
{
public:
	MouseProcessor();
	virtual void handleInput(int key, int upDown = 0, int x = 0, int y = 0);

	virtual void registerSelf(Entity* parent);


private:
	//The location of the mouse when dragging began
	int dragOriginX;
	int dragOriginY;

	//The coordinates of the parent control
	int* x;
	int* y;
	int* w;
	int* h;

	//True if the mouse is currently within the bounds of the control this is assigned to
	bool mouseIsWithin;

	//True if the control this is assigned to has been clicked on but not yet released
	bool mouseIsDownOnThis;

	//Tracks the time since the last mouse click
	Timer mouseTimer;
};
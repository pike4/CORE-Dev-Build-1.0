#pragma once

#include "Control.h"
#include "GUI_Area.h"

class DragArea : public Control
{
public:
	virtual void update();
	virtual void handleInput(int keyCode, int upDown = 0, int x = 0, int y = 0);

	DragArea(int x, int y, int w, int h, GUI_Area* owner);
	DragArea(pugi::xml_node node);

	virtual void registerSelf(Entity* parent);

	void setBounds(int minX, int maxX, int minY, int maxY, bool relative = true);
	SDL_Rect bounds;

protected:
	GUI_Area* owner;

	int initDragX, initDragY;

	virtual void handleMouseEnter();
	virtual void handleMouseLeave();
	virtual void handleMouseDown();
	virtual void handleMouseUp();

	void moveParent(int x, int y, bool relative = true);

	void handleDrag();
};
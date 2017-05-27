#pragma once

#include "Control.h"
#include "GUI_Area.h"

class MouseProcessor;

class DragArea : public Control
{
public:
	virtual void update();
	virtual void handleInput(int keyCode, int upDown = 0, int x = 0, int y = 0);

	DragArea(int x, int y, int w, int h, GUI_Area* owner);
	DragArea();

	virtual void finalize();

	virtual void get_data(DataSource* source);

	virtual void registerEvents(Entity* parent);

	void setBounds(int minX, int maxX, int minY, int maxY, bool relative = true);
	SDL_Rect bounds;

protected:
	GUI_Area* owner;

	//Please come up with a better alternative for static composition
	MouseProcessor* processor;

	int initDragX, initDragY;

	virtual void handleMouseEnter();
	virtual void handleMouseLeave();
	virtual void handleMouseDown();
	virtual void handleMouseUp();

	void moveParent(int x, int y, bool relative = true);

	void handleDrag();
};
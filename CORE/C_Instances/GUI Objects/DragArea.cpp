#include "DragArea.h"
#include "EventManager.h"

DragArea::DragArea(int x, int y, int w, int h, GUI_Area* owner)
	:Control(x, y, w, h)
{
	this->owner = owner;

	if (owner == NULL)
	{
		//TODO: Log Error
	}

	bounds = { 0, 0, 0, 0 };
}

DragArea::DragArea(pugi::xml_node node)
	:Control(node)
{

}

void DragArea::handleInput(int keyCode, int upDown, int x, int y)
{
	if (keyCode == mouseMoved && mouseIsDown)
	{
		handleDrag();
	}

	else if (keyCode == mouse1Down)
	{
		if(isWithin(x, y))
		mouseDown();
	}

	else if (keyCode == mouse1Up && mouseIsDown)
	{
		mouseUp();
	}
}

void DragArea::mouseEnter()
{
	
}

void DragArea::mouseLeave()
{

}

void DragArea::mouseDown()
{
	mouseIsDown = true;
	SDL_GetMouseState(&initDragX, &initDragY);

	initDragX -= *x;
	initDragY -= *y;
}

void DragArea::mouseUp()
{
	mouseIsDown = false;
}

void DragArea::handleDrag()
{
	int mouseX, mouseY;
	int destX, destY;

	SDL_GetMouseState(&mouseX, &mouseY);

	destX = mouseX - initDragX;
	destY = mouseY - initDragY;

	if (bounds.x)
	{
		if (destX < bounds.x)
		{
			destX = bounds.x;
		}

		else if (destX > bounds.w)
		{
			destX = bounds.w;
		}
	}

	if (bounds.y)
	{
		if (destY < bounds.y)
		{
			destY = bounds.y;
		}

		else if (destY > bounds.h)
		{
			destY = bounds.h;
		}
	}

	moveParent(destX, destY, false);
}

void DragArea::moveParent(int x, int y, bool relative)
{
	owner->move(x, y);
}

void DragArea::setBounds(int minX, int maxX, int minY, int maxY, bool relative)
{
	if (relative)
	{
		bounds.x = minX + *x;
		bounds.w = maxX + *x;
		bounds.y = minY + *y;
		bounds.h = maxY + *y;
	}

	else
	{
		bounds.x = minX;
		bounds.w = maxX;
		bounds.y = minY;
		bounds.h = maxY;
	}
}

void DragArea::update(){}
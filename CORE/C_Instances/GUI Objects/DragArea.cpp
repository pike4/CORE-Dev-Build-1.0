#include "DragArea.h"
#include "EventManager.h"
#include "MouseProcessor.h"

DragArea::DragArea(int aX, int aY, int aW, int aH, GUI_Area* owner)
	:Control(aX, aY, aW, aH)
{
	this->owner = owner;

	if (owner == NULL)
	{
		//TODO: Log Error
	}

	bounds = { 0, 0, 0, 0 };


	//By default, set drag area w and h to that of parent
	if (!w && parent)
	{
		w = (int*) parent->getPointer("w", sizeof(int));
	}

	if (!h && parent)
	{
		h = (int*) parent->getPointer("h", sizeof(int));
	}
}

DragArea::DragArea(pugi::xml_node node)
	:Control(node)
{
	events.push_back(mouse1Down);
	events.push_back(mouseMoved);
	events.push_back(mouse1Up);

	//By default, set drag area w and h to that of parent
	if (!(*w) && parent)
	{
		w = (int*) parent->getPointer("w", sizeof(int));
	}

	if (!(*h) && parent)
	{
		h = (int*) parent->getPointer("h", sizeof(int));
	}

	components.push_back(new MouseProcessor());
}

void DragArea::handleInput(int keyCode, int upDown, int aX, int aY)
{
	switch (keyCode)
	{
	case mouseDrag:
		int mouseX = 0;
		int mouseY = 0;

		SDL_GetMouseState(&mouseX, &mouseY);
		
		parent->handleInput(updatePos, 0, mouseX - aX, mouseY - aY);
		break;
	}
	Entity::handleInput(keyCode, upDown, aX, aY);
}

void DragArea::registerSelf(Entity* parent)
{
	if (parent && *w == 0)
	{
		w = (int*) setPointer("w", sizeof(int), parent->getPointer("w", sizeof(int)));
	}

	if (parent && *h == 0)
	{
		h = (int*) setPointer("h", sizeof(int), parent->getPointer("h", sizeof(int)));
	}
	Control::registerSelf(parent);
}

void DragArea::handleMouseEnter()
{
	
}

void DragArea::handleMouseLeave()
{

}

void DragArea::handleMouseDown()
{
	mouseIsDown = true;
	SDL_GetMouseState(&initDragX, &initDragY);

	initDragX -= *x;
	initDragY -= *y;
}

void DragArea::handleMouseUp()
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
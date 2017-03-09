#include "DragArea.h"
#include "CORE_Devices.h"
#include "MouseProcessor.h"

DragArea::DragArea(int aX, int aY, int aW, int aH, GUI_Area* owner)
{
	this->owner = owner;

	if (owner == NULL)
	{
		//TODO: Log Error
	}

	bounds = { 0, 0, 0, 0 };

	//By default, set drag area w and h to that of parent
	if (!(*w) && parent)
	{
		w->addDependency(parent->getData<int>("w"));
	}

	if (!(*h) && parent)
	{
		h->addDependency(parent->getData<int>("h"));
	}
}

DragArea::DragArea()
	:Control()
{
	events.push_back(mouse1Down);
	events.push_back(mouseMoved);
	events.push_back(mouse1Up);

	processor = new MouseProcessor();
}

void DragArea::finalize()
{
	processor->parent = this;
	processor->finalize();
	processor->registerEvents(this);
}

void DragArea::get_data(DataSource* source)
{
	Control::get_data(source);

	processor->x = x;
	processor->y = y;
	processor->w = w;
	processor->h = h;
}

void DragArea::handleInput(int keyCode, int upDown, int aX, int aY)
{
	switch (keyCode)
	{
	case mouseDrag:
		int mouseX = 0;
		int mouseY = 0;

		SDL_GetMouseState(&mouseX, &mouseY);
		
		//parent->handleInput(updatePos, 0, mouseX - aX, mouseY - aY);
		*x = (mouseX - aX);
		*y = (mouseY - aY);
		break;
	}
	processor->handleInput(keyCode, upDown, aX, aY);
	Entity::handleInput(keyCode, upDown, aX, aY);
}

void DragArea::registerEvents(Entity* parent)
{
	//Get parent dimensions if dimensoins were left uninitialized at construction
	if (parent && *w == 0)
	{
		setData("w", parent->getData<int>("w"));
		w = getData<int>("w");
	}

	if (parent && *h == 0)
	{
		setData("h", parent->getData<int>("h"));
		h = getData<int>("h");
	}
	Control::registerEvents(parent);
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

void DragArea::moveParent(int aX, int aY, bool relative)
{
	
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
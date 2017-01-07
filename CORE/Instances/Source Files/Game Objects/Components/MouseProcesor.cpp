#include "MouseProcessor.h"
#include "QuadTree.h"
#include "Entity.h"
#include "Data.h"

bool isWithin(int pointX, int pointY, int rectX, int rectY, int rectW, int rectH)
{
	return ((pointX > rectX) && (pointX < (rectX + rectW)) 
		&& (pointY > rectY) && (pointY < (rectY + rectH)));
}

MouseProcessor::MouseProcessor()
{
	events.push_back(mouseMoved);
	events.push_back(mouse1Down);
	events.push_back(mouse1Up);
}

void MouseProcessor::handleInput(int key, int upDown, int aX, int aY)
{
	if (!parent)
	{
		return;
	}
	bool newWithin = false;
	switch (key)
	{
	
	case mouseMoved:
		newWithin = isWithin(aX, aY, *x, *y, *w, *h);

		if (mouseIsDownOnThis)
		{
			parent->handleInput(mouseDrag, true, dragOriginX, dragOriginY);
		}
		
		if (!mouseIsWithin && newWithin)
		{
			mouseIsWithin = true;
			parent->handleInput(mouseEnter);
		}

		else if (mouseIsWithin && !newWithin)
		{
			mouseIsWithin = false;
			parent->handleInput(mouseLeave);
		}
		break;

	case mouse1Down:
		if (isWithin(aX, aY, *x, *y, *w, *h))
		{
			mouseIsDownOnThis = true;
			dragOriginX = aX - *x;
			dragOriginY = aY - *y;
			parent->handleInput(mousePress);
		}

		if (!mouseTimer.hasElapsed(0))
		{
			parent->handleInput(doubleClick);
		}

		mouseTimer.updateTime();
		break;

	case mouse1Up:
		if (mouseIsDownOnThis)
		{
			mouseIsDownOnThis = false;
			parent->handleInput(mouseRelease);
		}
		break;
	}
}

void MouseProcessor::registerSelf(Entity* parent)
{
	Component::registerSelf(parent);
	x = (DataOffset<int>*) parent->getCompoundData<DataOffset<int>>("x");
	y = (DataOffset<int>*) parent->getCompoundData<DataOffset<int>>("y");
	w = parent->getData<int>("w");
	h = parent->getData<int>("h");
}
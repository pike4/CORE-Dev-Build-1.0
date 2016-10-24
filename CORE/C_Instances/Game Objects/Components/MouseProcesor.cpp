#include "MouseProcessor.h"
#include "QuadTree.h"
#include "Entity.h"

bool isWithin(int pointX, int pointY, int rectX, int rectY, int rectW, int rectH)
{
	return ((pointX > rectX) && (pointX < (rectX + rectW)) 
		&& (pointY > rectY) && (pointY < (rectY + rectH)));
}

MouseProcessor::MouseProcessor()
{
	int a[] = { mouse1Down, mouseMoved, mouse1Up};
	events.insert(events.begin(), a, a + 2);
}

void MouseProcessor::handleInput(int key, int upDown, int x, int y)
{
	if (!parent)
	{
		return;
	}
	bool newWithin = false;
	switch (key)
	{
	
	case mouseMoved:
		newWithin = isWithin(x, y, 0, 0, 0, 0);

		if (mouseIsDownOnThis)
		{
			parent->handleInput(mouseDrag, true, x, y);
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
		if (isWithin(x, y, 0, 0, 0, 0))
		{
			mouseIsDownOnThis = true;
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
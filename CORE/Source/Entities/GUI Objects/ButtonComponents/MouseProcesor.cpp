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

void MouseProcessor::handle(Event e)
{
	if (!parent)
	{
		return;
	}
	bool newWithin = false;
	switch (e.opcode)
	{
      DataImpl<int>* aX;
      DataImpl<int>* aY;

	case mouseMoved:
      aX = (DataImpl<int>*) e.arguments[0].data;
      aY = (DataImpl<int>*) e.arguments[1].data;

		newWithin = isWithin(*aX, *aY, *x, *y, *w, *h);

		if (mouseIsDownOnThis)
		{
         Event dragEvent = mouseDrag;
         DataImpl<int> doX;
         doX = dragOriginX;
         DataImpl<int> doY;
         doY = dragOriginY;
         DataImpl<bool> isUp;
         isUp = true;
         dragEvent.arguments = { &doX, &doY, &isUp };

			parent->handle(dragEvent);
		}
		
		if (!mouseIsWithin && newWithin)
		{
			mouseIsWithin = true;
			parent->handle(mouseEnter);
		}

		else if (mouseIsWithin && !newWithin)
		{
			mouseIsWithin = false;
			parent->handle(mouseLeave);
		}
		break;

	case mouse1Down:
      aX = (DataImpl<int>*) e.arguments[1].data;
      aY = (DataImpl<int>*) e.arguments[2].data;

		if (isWithin(*aX, *aY, *x, *y, *w, *h))
		{
			mouseIsDownOnThis = true;
			dragOriginX = *aX - *x;
			dragOriginY = *aY - *y;
			parent->handle(mousePress);
		}

		if (!mouseTimer.hasElapsed(0))
		{
			parent->handle(doubleClick);
		}

		mouseTimer.updateTime();
		break;

	case mouse1Up:
		if (mouseIsDownOnThis)
		{
			mouseIsDownOnThis = false;
			parent->handle(mouseRelease);
		}
		break;
	}
}
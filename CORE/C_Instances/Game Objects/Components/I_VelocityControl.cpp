#include "I_VelocityControl.h"
#include "GameObject.h"

Component* I_VelocityControl::spawnCopy()
{
	return new I_VelocityControl(*this);
}

I_VelocityControl::I_VelocityControl(pugi::xml_node node)
{
	x = NULL;
	y = NULL;
	xVel = NULL;
	yVel = NULL;

	events = { walkBackwardButtonDown, walkBackwardButtonUp, walkDownButtonDown, walkDownButtonUp, walkForwardButtonDown, walkDownButtonUp, walkLeftButtonDown, walkLeftButtonUp, walkRightButtonDown, walkRightButtonUp, updateStep };
}

I_VelocityControl::I_VelocityControl(I_VelocityControl& other)
{
	x = NULL;
	y = NULL;
	xVel = NULL;
	yVel = NULL;
	events = { walkBackwardButtonDown, walkBackwardButtonUp, walkDownButtonDown, walkDownButtonUp, walkForwardButtonDown, walkDownButtonUp, walkLeftButtonDown, walkLeftButtonUp, walkRightButtonDown, walkRightButtonUp, updateStep };
}

void I_VelocityControl::assignPointers(GameObject* parent)
{
	x = (int*)parent->getPointer("x", sizeof(int));
	y = (int*)parent->getPointer("y", sizeof(int));
	xVel = (double*)parent->getPointer("xVel", sizeof(double));
	yVel = (double*)parent->getPointer("yVel", sizeof(double));

	*x = 0;
	*y = 0;
	*xVel = 0;
	*yVel = 0;
}

void I_VelocityControl::handleInput(int key, int upDown, int a_x, int a_y)
{
	int yy = *yVel;
	switch (key)
	{
	case updateStep:
		*x += *xVel;
		*y += *yVel;
		break;
	case walkBackwardButtonDown:
		if (upDown)
		{
			*yVel += 2;
		}

		else
		{
			*yVel -= 2;
		}
		break;
	case walkForwardButtonDown:
		if (upDown)
		{
			*yVel -= 2;
		}

		else
		{
			*yVel += 2;
		}
		break;
	case walkLeftButtonDown:
		if (upDown)
		{
			*xVel -= 2;
		}

		else
		{
			*xVel += 2;
		}
		break;
	case walkRightButtonDown:
		if (upDown)
		{
			*xVel += 2;
		}

		else
		{
			*xVel -= 2;
		}
		break;

	}
}

void I_VelocityControl::move(int aX, int aY)
{
	*x = aX;
	*y = aY;
}
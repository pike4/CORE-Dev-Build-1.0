#include "I_VelocityControl.h"
#include "Entity.h"
#include "Node.h"

Component* I_VelocityControl::spawnCopy()
{
	return new I_VelocityControl(*this);
}

I_VelocityControl::I_VelocityControl()
{
	x = NULL;
	y = NULL;
	xVel = NULL;
	yVel = NULL;

	events = { walkBackwardButtonDown, walkBackwardButtonUp, walkDownButtonDown, walkDownButtonUp, walkForwardButtonDown, walkDownButtonUp, walkLeftButtonDown, walkLeftButtonUp, walkRightButtonDown, walkRightButtonUp, updateStep };
}

I_VelocityControl::I_VelocityControl(I_VelocityControl& other) : I_VelocityControl()
{

}

void I_VelocityControl::handle(Event e)
{
	Velocity::handle(e);
   bool upDown;
	switch (e.opcode)
	{
	case walkBackwardButtonDown:
      upDown = *((DataImpl<bool>*) e.arguments[0].data);
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
      upDown = *((DataImpl<bool>*) e.arguments[0].data);
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
      upDown = *((DataImpl<bool>*) e.arguments[0].data);
		if (upDown)
		{
			*xVel = *xVel - 2;
		}

		else
		{
			*xVel = *xVel + 2;
		}
		break;
	case walkRightButtonDown:
      upDown = *((DataImpl<bool>*) e.arguments[0].data);
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
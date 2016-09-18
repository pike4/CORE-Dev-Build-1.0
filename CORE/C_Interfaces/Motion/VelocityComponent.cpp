#include "MotionAffector.h"
#include "VelocityComponent.h"
#include "GameObject.h"

VelocityComponent::VelocityComponent(pugi::xml_node node)
{
	pugi::xml_node tempNode = node.first_child();
	std::string tempName = tempNode.name();
}

void VelocityComponent::move(int x, int y)
{}

void VelocityComponent::addTo(Room*)
{}

void VelocityComponent::updatePos()
{
	parent->x += xVel;
	parent->y += yVel;

	parent->move(parent->x, parent->y);
}

void VelocityComponent::handleInput(int keyCode, int upDown, int x, int y)
{
	switch (keyCode)
	{
	case walkBackwardButtonDown:
		if (upDown)
		{
			yVel = 2;
		}

		else
		{
			yVel = 0;
		}
		break;
	case walkForwardButtonDown:
		if (upDown)
		{
			yVel = -2;
		}

		else
		{
			yVel = 0;
		}
		break;
	case walkLeftButtonDown:
		if (upDown)
		{
			xVel = -2;
		}

		else
		{
			xVel = 0;
		}
		break;
	case walkRightButtonDown:
		if (upDown)
		{
			xVel = 2;
		}

		else
		{
			xVel = 0;
		}
		break;
	}

}

Mover* VelocityComponent::spawnCopy()
{
	return new VelocityComponent(*this);
}
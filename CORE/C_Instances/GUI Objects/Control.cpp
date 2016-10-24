#pragma once
#include "Control.h"
#include "EventManager.h"
#include "ObjectManager.h"
#include "pugixml.hpp"

Control::Control()
	:Entity()
{
	events = { drawStep, updateStep };
}

Control::Control(pugi::xml_node node) : Entity(node)
{
	x = (int*)getPointer("x", sizeof(int));
	y = (int*)getPointer("y", sizeof(int));

	getArgsFromNode(node);
}

Control::Control(pugi::xml_node node, Aggregate* parent) : Control(node)
{

}

Control::Control(pugi::xml_node node, std::vector<BaseObject*>* objectVector, std::vector<Drawable*>* visibleVector)
{
	getArgsFromNode(node);
}

Control::Control(pugi::xml_node node, MenuScreen* parent) : Control(node)
{
	
}

Control::Control(int aX, int aY, int aW, int aH)
{
	w = aW;
	h = aH;
}

void Control::getArgsFromNode(pugi::xml_node node)
{
	w = atoi(node.child("w").first_child().value());
	h = atoi(node.child("h").first_child().value());
}

bool Control::isWithin(int aX, int aY)
{
	return (aX > *x && aX < *x + w && aY > *y && aY < *y + h);
}

void Control::handleInput(int keyCode, int upDown, int x, int y)
{
	Entity::handleInput(keyCode, upDown, x, y);

	switch (keyCode)
	{
	case drawStep:
		if (!hidden)
		{
			for each(VisibleElement* element in elements)
			{
				element->draw();
			}
		}
		break;

	case mouseMoved:
		if (isWithin(x, y))
		{
			//event mouse hover
		}

		else if (mouseHovering)
		{
			//event mouse leave
			if (cancelInputOnMouseLeave)
			{
				mouseIsDown = false;
			}
		}
		break;

	case mouse1Down:
		if (mouseHovering)
		{
			mouseIsDown = true;
			//event mouse down
		}
		break;

	case mouse1Up:
		if (mouseIsDown)
		{
			//event mouse release
		}
		break;

	default:
		break;
	}
}

void Control::show()
{
	hidden = false;
}

void Control::hide()
{
	hidden = true;
}
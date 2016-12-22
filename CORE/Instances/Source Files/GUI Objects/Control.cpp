#pragma once
#include "Control.h"
#include "EventManager.h"
#include "ObjectManager.h"
#include "pugixml.hpp"

Control::Control()
{
	events = { drawStep, updateStep, updatePos };
}

Control::Control(pugi::xml_node node) : Entity(node)
{
	events = { drawStep, updateStep, updatePos };
	x = (int*)getPointer("x", sizeof(int));
	y = (int*)getPointer("y", sizeof(int));

	xOffset = (int*)getPointer("xOffset", sizeof(int));
	yOffset = (int*)getPointer("yOffset", sizeof(int));

	w = (int*)getPointer("w", sizeof(int));
	h = (int*)getPointer("h", sizeof(int));

	getArgsFromNode(node);
}

void Control::move(int aX, int aY)
{
	*x = aX + *xOffset;
	*y = aY + *yOffset;
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
	*w = aW;
	*h = aH;
}

void Control::getArgsFromNode(pugi::xml_node node)
{
	*xOffset = atoi(node.child("xOffset").first_child().value());
	*yOffset = atoi(node.child("yOffset").first_child().value());
	*w = atoi(node.child("w").first_child().value());
	*h = atoi(node.child("h").first_child().value());
}

void Control::registerSelf(Entity* parent)
{
	this;
	if (parent)
	{
		x = (int*)setPointer("x", sizeof(int), parent->getPointer("x", sizeof(int)));
		y = (int*)setPointer("y", sizeof(int), parent->getPointer("y", sizeof(int)));
	}

	Entity::registerSelf(parent);
}

bool Control::isWithin(int aX, int aY)
{
	return (aX > *x && aX < *x + *w && aY > *y && aY < *y + *h);
}

void Control::handleInput(int keyCode, int upDown, int aX, int aY)
{
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
		if (isWithin(aX, aY))
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

	case updatePos:
		*x = aX;
		*y = aY;
		break;


	default:
		break;
	}

	Entity::handleInput(keyCode, upDown, aX, aY);
}

void Control::show()
{
	hidden = false;
}

void Control::hide()
{
	hidden = true;
}
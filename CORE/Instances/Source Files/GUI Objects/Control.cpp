#pragma once
#include "Control.h"
#include "EventManager.h"
#include "ObjectManager.h"
#include "pugixml.hpp"

Control::Control()
{
	events = { drawStep, updateStep, updatePos };

	x = (DataOffset<int>*) getCompoundData<DataOffset<int>>("x");
	y = (DataOffset<int>*) getCompoundData<DataOffset<int>>("y");
}

Control::Control(pugi::xml_node node) : Entity(node)
{
	events = { drawStep, updateStep, updatePos };

	x = (DataOffset<int>*) getCompoundData<DataOffset<int>>("x");
	y = (DataOffset<int>*) getCompoundData<DataOffset<int>>("y");

	w = getData<int>("w");
	h = getData<int>("h");

	getArgsFromNode(node);
}

//This is marked for death
void Control::move(int aX, int aY)
{
	*x = aX;
	*y = aY;
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

}

void Control::getArgsFromNode(pugi::xml_node node)
{
	*x = atoi(node.child("xOffset").first_child().value());
	*y = atoi(node.child("yOffset").first_child().value());

	*w = atoi(node.child("w").first_child().value());
	*h = atoi(node.child("h").first_child().value());
}

void Control::registerSelf(Entity* parent)
{
	this;
	if (parent)
	{
		x->addDependency((DataOffset<int>*) parent->getCompoundData<DataOffset<int>>("x"));
		y->addDependency((DataOffset<int>*) parent->getCompoundData<DataOffset<int>>("y"));
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
	this;
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
#pragma once
#include "Control.h"
#include "CORE_Devices.h"
#include "CORE_Factory.h"
#include "pugixml.hpp"

Control::Control()
{
	events = { drawStep, updateStep, updatePos };

	x = (DataOffset<int>*) getCompoundData<DataOffset<int>>("x");
	y = (DataOffset<int>*) getCompoundData<DataOffset<int>>("y");
}

Control::Control(Definer* definer) : Entity(definer)
{
	events = { drawStep, updateStep, updatePos };

	x = (DataOffset<int>*) getCompoundData<DataOffset<int>>("x");
	y = (DataOffset<int>*) getCompoundData<DataOffset<int>>("y");

	w = getData<int>("w");
	h = getData<int>("h");

	getArgsFromNode(definer);
}

//This is marked for death
void Control::move(int aX, int aY)
{
	*x = aX;
	*y = aY;
}

Control::Control(Definer* definer, MenuScreen* parent) : Control(definer)
{
	
}

Control::Control(int aX, int aY, int aW, int aH)
{

}

void Control::getArgsFromNode(Definer* definer)
{
	*x = stoi(definer->getVariable("xOffset"));
	*y = stoi(definer->getVariable("yOffset"));
	*w = stoi(definer->getVariable("w"));
	*h = stoi(definer->getVariable("h"));
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
#pragma once
#include "Control.h"
#include "CORE_Devices.h"
#include "CORE_Factory.h"
#include "pugixml.hpp"

Control::Control()
{
	events = { drawStep, updateStep, updatePos };
}


void Control::get_data(DataSource* source)
{
   Entity::get_data(source);
	x = source->getData<int>("x");
	y = source->getData<int>("y");

	w = source->getData<int>("w");
	h = source->getData<int>("h");
}

bool Control::isWithin(int aX, int aY)
{
	return (aX > *x && aX < *x + *w && aY > *y && aY < *y + *h);
}

void Control::handle(Event e)
{
   DataImpl<int>* aX;
   DataImpl<int>* aY;

	switch (e.opcode)
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
      aX = (DataImpl<int>*) e.arguments[0].data;
      aY = (DataImpl<int>*) e.arguments[1].data;
		if (isWithin(*aX, *aY))
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
      aX = (DataImpl<int>*) e.arguments[0].data;
      aY = (DataImpl<int>*) e.arguments[1].data;

		*x = *aX;
		*y = *aY;
		break;

	default:
		break;
	}
	this;
   Entity::handle(e);
}

void Control::show()
{
	hidden = false;
}

void Control::hide()
{
	hidden = true;
}
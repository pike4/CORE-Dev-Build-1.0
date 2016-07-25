#pragma once
#include "Control.h"
#include "EventManager.h"
#include "pugixml.hpp"

Control::Control(pugi::xml_node node)
	:Drawable(node)
{
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

Control::Control(int x, int y, int w, int h)
{
	box = { x, y, w, h };
}

void Control::getArgsFromNode(pugi::xml_node node)
{
	box.x = atoi(node.child("x").first_child().value());
	box.y = atoi(node.child("y").first_child().value());
	box.w = atoi(node.child("w").first_child().value());
	box.h = atoi(node.child("h").first_child().value());
}

int Control::getX()
{
	return box.x;
}

int Control::getY()
{
	return box.y;
}

bool Control::isWithin(int x, int y)
{
	return (x > box.x && x < box.x + box.w && y > box.y && y < box.y + box.h);
}

void Control::update() {}

void Control::draw(SDL_Renderer* renderer)
{
	for each(VisibleElement* element in elements)
	{
		element->draw(renderer);
	}
}

void Control::move(int x, int y, bool relative)
{
	int deltaX, deltaY;
	if (relative)
	{
		deltaX = x;
		deltaY = y;
	}

	else
	{
		deltaX = x - box.x;
		deltaY = y - box.y;
	}

	for (int i = 0; i < elements.size(); i++)
	{
		VisibleElement* element = elements[i];
		element->box.x += deltaX;
		element->box.y += deltaY;
	}

	box.x += deltaX;
	box.y += deltaY;
}

void Control::handleInput(int keyCode, int upDown, int x, int y)
{
	switch (keyCode)
	{
	case mouseMoved:
		if (isWithin(x, y))
		{
			mouseEnter();
		}

		else if (mouseHovering)
		{
			mouseLeave();
			if (cancelInputOnMouseLeave)
			{
				mouseIsDown = false;
			}
		}
		break;

	case mouse1Down:
		if (mouseHovering)
		{
			mouseDown();
		}
		break;

	case mouse1Up:
		if (mouseIsDown)
		{
			mouseUp();
		}
		break;

	default:
		break;
	}
}
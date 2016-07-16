#pragma once
#include "Control.h"
#include "pugixml.hpp"

Control::Control(pugi::xml_node node) : BaseObject(node), Visible(node)
{
	getArgsFromNode(node);

	boundingBox.x = x;
	boundingBox.y = y;
}

Control::Control(pugi::xml_node node, Aggregate* parent) : Control(node)
{

}

Control::Control(pugi::xml_node node, std::vector<BaseObject*>* objectVector, std::vector<Visible*>* visibleVector) : BaseObject(node, objectVector), Visible(node, visibleVector)
{
	getArgsFromNode(node);
}

Control::Control(pugi::xml_node node, MenuScreen* parent) : Control(node)
{
	
}

void Control::getArgsFromNode(pugi::xml_node node)
{
	boundingBox.w = atoi(node.child("w").first_child().value());
	boundingBox.h = atoi(node.child("h").first_child().value());
}

int Control::getX()
{
	return boundingBox.x;
}

int Control::getY()
{
	return boundingBox.y;
}

bool Control::isWithin(int x, int y)
{
	return (x > this->x && x < this->x + this->boundingBox.w && y > this->y && y < this->y + this->boundingBox.h);
}

void Control::update() {}

void Control::draw(SDL_Renderer* renderer)
{
	for each(VisibleElement* element in elements)
	{
		element->draw(renderer);
	}
}
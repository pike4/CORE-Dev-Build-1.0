#include "Drawable.h"
#include "pugixml.hpp"
#include "SDL.h"
#include "RenderableCharSet.h"
#include "VisibleElement.h"
#include "VideoManager.h"
#include "Room.h"

VisibleElement::VisibleElement()
{
	pointers.push_back({ "x", sizeof(int), &x });
	pointers.push_back({ "y", sizeof(int), &y });

	events.push_back(drawStep);
}

VisibleElement::VisibleElement(int x, int y, int aW, int aH)
	:VisibleElement()
{
	w = aW;
	h = aH;
}

VisibleElement::VisibleElement(pugi::xml_node node)
	:VisibleElement()
{
	w = atoi(node.child("w").first_child().value());
	h = atoi(node.child("h").first_child().value());

	parentOffsetX = atoi(node.child("X_Offset").first_child().value());
	parentOffsetY = atoi(node.child("Y_Offset").first_child().value());
}


VisibleElement::VisibleElement(VisibleElement& other)
	:VisibleElement()
{}

void VisibleElement::move(int x, int y)
{}

void VisibleElement::addTo(Room* room)
{
	if (room != NULL)
	{
		room->drawVector->push_back(this);
	}
}

void VisibleElement::handleInput(int key, int upDown, int x, int y)
{
	switch (key)
	{
	case drawStep:
		draw();
		break;
	}
}
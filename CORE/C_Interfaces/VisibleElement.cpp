#include "Drawable.h"
#include "pugixml.hpp"
#include "SDL.h"
#include "RenderableCharSet.h"
#include "VisibleElement.h"
#include "VideoManager.h"
#include "Room.h"

VisibleElement::VisibleElement(int x, int y, int w, int h)
{
	box = { x, y, w, h };
}

VisibleElement::VisibleElement(pugi::xml_node node)
{
	box.x = atoi(node.child("x").first_child().value());
	box.y = atoi(node.child("y").first_child().value());
	box.w = atoi(node.child("w").first_child().value());
	box.h = atoi(node.child("h").first_child().value());

	parentOffsetX = atoi(node.child("X_Offset").first_child().value());
	parentOffsetY = atoi(node.child("Y_Offset").first_child().value());
}


VisibleElement::VisibleElement(VisibleElement& other)
{
	box = other.box;
}

void VisibleElement::move(int x, int y)
{
	box.x = x;
	box.y = y;
}

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
		draw(VideoManager::mRenderer);
		break;
	}
}
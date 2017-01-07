#include "Drawable.h"
#include "pugixml.hpp"
#include "SDL.h"
#include "RenderableCharSet.h"
#include "VisibleElement.h"
#include "VideoManager.h"
#include "Room.h"

VisibleElement::VisibleElement()
{
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
	//*X = atoi(node.child("x").first_child().value());
	//*Y= atoi(node.child("y").first_child().value());
	w = atoi(node.child("w").first_child().value());
	h = atoi(node.child("h").first_child().value());

	zIndex = atoi(node.child("zIndex").first_child().value());
}


VisibleElement::VisibleElement(VisibleElement& other)
	:VisibleElement()
{
	zIndex = other.zIndex;
}

void VisibleElement::assignPointers(Entity* aParent)
{
	Component::assignPointers(aParent);

	X = (DataOffset<int>*) parent->getCompoundData<DataOffset<int>>("x");
	Y = (DataOffset<int>*) parent->getCompoundData<DataOffset<int>>("y");
}

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
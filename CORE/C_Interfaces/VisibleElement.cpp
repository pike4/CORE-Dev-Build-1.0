#include "Drawable.h"
#include "pugixml.hpp"
#include "SDL.h"
#include "RenderableCharSet.h"
#include "VisibleElement.h"

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

VisibleElement::VisibleElement(VisibleElement& copy)
{
	box = copy.box;
}

void VisibleElement::move(int x, int y)
{
	box.x = x;
	box.y = y;
}
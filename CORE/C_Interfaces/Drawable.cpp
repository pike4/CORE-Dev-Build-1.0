#include "Drawable.h"
#include "Room.h"

Drawable::Drawable()
{}

Drawable::Drawable(pugi::xml_node node)
{
	zIndex = atoi(node.child("Z-Index").first_child().value());
}


Drawable::Drawable(pugi::xml_node node, Room* room)
	:Drawable(node)
{
	room->drawVector->push_back(this);
}
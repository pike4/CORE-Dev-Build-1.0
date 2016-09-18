#include "Drawable.h"
#include "Room.h"
#include "ObjectManager.h"

Drawable::Drawable()
{}

Drawable::Drawable(pugi::xml_node node)
{
	zIndex = atoi(node.child("Z-Index").first_child().value());
}


Drawable::Drawable(pugi::xml_node node, Room* room)
	:Drawable(node)
{
	add(room);
}

void Drawable::add(Room* room)
{
	if (room != NULL)
	{
		room->drawVector->push_back(this);
	}
}
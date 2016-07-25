#include "SimpleDrawable.h"
#include "ObjectManager.h"

SimpleDrawable::SimpleDrawable(pugi::xml_node node)
{
	element = ObjectManager::generateVisibleElement(node.child("VisibleElement").first_child().name(), node.child("VisibleElement").first_child());

	int tempZIndex = atoi(node.child("Z-Index").first_child().value());
	tempZIndex = atoi(node.first_child().value());
	zIndex = tempZIndex;
}

SimpleDrawable::SimpleDrawable(pugi::xml_node node, Room* room)
	:SimpleDrawable(node)
{
	room->drawVector->push_back(this);
}

void SimpleDrawable::move(int x, int y)
{
	element->box.x = x + element->parentOffsetY;
	element->box.y = y + element->parentOffsetY;
}
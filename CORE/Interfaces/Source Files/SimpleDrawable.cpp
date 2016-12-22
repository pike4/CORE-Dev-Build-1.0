#include "SimpleDrawable.h"
#include "ObjectManager.h"

SimpleDrawable::SimpleDrawable(pugi::xml_node node)
{
	element = ObjectManager::generateVisibleElement(node.child("VisibleElement").first_child().name(), node.child("VisibleElement").first_child());
}

SimpleDrawable::SimpleDrawable(pugi::xml_node node, Room* room)
	:SimpleDrawable(node)
{
	room->drawVector->push_back(this);
}

void SimpleDrawable::move(int x, int y)
{
	element->move(x, y);
}
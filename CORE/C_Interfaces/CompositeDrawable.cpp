#include "CompositeDrawable.h"
#include "ObjectManager.h"

CompositeDrawable::CompositeDrawable(pugi::xml_node node)
	: VisibleElement(node)
{
	pugi::xml_node curNode;
	std::string curName;

	 curNode = node.child("VisibleElements").first_child();
	 curName = curNode.name();

	 while (!curName.empty())
	 {
		 elements.push_back(ObjectManager::generateVisibleElement(curName, curNode));

		 curNode = curNode.next_sibling();
		 curName = curNode.name();
	 }

	int tempZIndex = 0;
	tempZIndex = atoi(node.child("Z-Index").first_child().value());
	zIndex = tempZIndex;

	node = node.next_sibling();
	curName = node.name();
}

CompositeDrawable::CompositeDrawable(pugi::xml_node node, Room* room)
	:CompositeDrawable(node)
{
	room->drawVector->push_back(this);
}

CompositeDrawable::CompositeDrawable(CompositeDrawable& other)
	:VisibleElement(other)
{
	zIndex = other.zIndex;

	for (int i = 0; i < other.elements.size(); i++)
	{
		elements.push_back(other.elements[i]->spawnCopy());
	}
}

VisibleElement* CompositeDrawable::spawnCopy()
{
	return new CompositeDrawable(*this);
}

CompositeDrawable::CompositeDrawable(CompositeDrawable& other, Room* room)
	:CompositeDrawable(other)
{
	room->drawVector->push_back(this);
}

void CompositeDrawable::move(int x, int y)
{
	for (int i = 0; i < elements.size(); i++)
	{
		elements[i]->box.x = x + elements[i]->parentOffsetX;
		elements[i]->box.y = y + elements[i]->parentOffsetY;
	}
}
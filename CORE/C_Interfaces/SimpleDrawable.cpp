#include "SimpleDrawable.h"
#include "ObjectManager.h"

SimpleDrawable::SimpleDrawable(pugi::xml_node node)
{
	node = node.first_child();
	std::string curName = node.name();

	while (!curName.empty())
	{
		if (!curName.compare("Visible Element"))
		{
			element = ObjectManager::generateVisibleElement(node.first_child().name(), node.first_child());
		}

		else if (!curName.compare("Z-Index"))
		{
			int tempZIndex = 0;
			tempZIndex = atoi(node.first_child().value());
			zIndex = tempZIndex;
		}

		else
		{
			//TODO log error: nonstandard element detected in xml file
		}

		node = node.next_sibling();
		curName = node.name();
	}
}

SimpleDrawable::SimpleDrawable(pugi::xml_node node, Room* room)
	:SimpleDrawable(node)
{
	room->drawVector->push_back(this);
}
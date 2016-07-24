#include "CompositeDrawable.h"
#include "ObjectManager.h"

CompositeDrawable::CompositeDrawable(pugi::xml_node node)
{
	node = node.first_child();
	std::string curName = node.name();

	while (!curName.empty())
	{
		if (!curName.compare("Visible Element"))
		{
			elements.push_back(ObjectManager::generateVisibleElement(node.first_child().name(), node.first_child()));
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

CompositeDrawable::CompositeDrawable(pugi::xml_node node, Room* room)
	:CompositeDrawable(node)
{
	room->drawVector->push_back(this);
}
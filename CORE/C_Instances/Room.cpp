#include "Room.h"
#include "SystemManager.h"

Room::Room(pugi::xml_node node)
{
	node = node.first_child();

	updateVector = new std::vector<Updatable*>;
	drawVector = new std::vector<Visible*>;
	objectVector = new std::vector<BaseObject*>;
	collidableVector = new std::vector<Collidable*>;

	do
	{
		if (strcmp(node.name(), "objects") == 0)
		{
			char* objectFileName = (char*)node.first_child().value();

			if (strcmp(objectFileName, "") != 0)
			{
				SystemManager::loadGameObjects(objectFileName, objectVector, drawVector, updateVector, collidableVector);
			}


		}
		node = node.next_sibling();
	} while (strcmp(node.name(), "") != 0);
}
#include "Room.h"
#include "SystemManager.h"

Room::Room(pugi::xml_node node)
{
	getArgsFromNode(node);
}

Room::Room(char* fileName)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load(fileName);

	pugi::xml_node curNode = doc.first_child();

	if (strcmp(curNode.name(), "Room"))
	{
		if (!strcmp("", fileName))
		{
			fileName = "NO NAME GIVEN";
		}
		printf("Attempted to load Room from malformed xml file: %s", fileName);
		return;
	}

	curNode = curNode.first_child();

	getArgsFromNode(curNode);
}

void Room::getArgsFromNode(pugi::xml_node node)
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

		else if (!strcmp(node.name(), "name"))
		{
			name = node.first_child().value();
		}
		node = node.next_sibling();
	} while (strcmp(node.name(), "") != 0);
}
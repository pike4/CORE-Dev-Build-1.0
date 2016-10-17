#include "Environment.h"
#include "StateManager.h"
#include "pugixml.hpp"

Environment::Environment(std::string fileName)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(fileName.c_str());

	pugi::xml_node curNode = doc.first_child();

	//If loading directly from a file, this should be defined in the first node
	if (strcmp(curNode.name(), "Environment"))
	{
		printf("Attempted to load Environment from malformed xml file");
		return;
	}

	curNode = curNode.first_child();
	getArgsFromNode(curNode);
	StateManager::environments[name] = this;

	if (name.empty())
	{
		printf("No environment name detected in file: %s. Consider adding a <name> node to this file\n", fileName.c_str());
		name = "Default Room";
	}
}

Environment::Environment(pugi::xml_node node)
{
	getArgsFromNode(node);
	StateManager::environments[name] = this;
}

void Environment::getArgsFromNode(pugi::xml_node node)
{
	std::string curName = node.name();

	while (!curName.empty())
	{
		if (!curName.compare("name"))
		{
			name = node.first_child().value();
		}

		else if (!curName.compare("Room"))
		{
			Room* roomToAdd = NULL;

			if (!strcmp(node.first_child().name(), "file"))
			{
				roomToAdd = new Room(node.first_child().value());
			}

			else
			{
				roomToAdd = new Room(node);
			}

			if (roomToAdd == NULL)
			{
				//TODO log error: NULL room added
			}

			rooms[roomToAdd->name] = roomToAdd;
		}

		node = node.next_sibling();
		curName = node.name();
	}
}
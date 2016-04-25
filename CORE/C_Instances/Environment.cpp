#include "Environment.h"
#include "StateManager.h"
#include "pugixml.hpp"

Environment::Environment(char* fileName)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(fileName);

	pugi::xml_node curNode = doc.first_child();

	if (strcmp(curNode.name(), "Environment"))
	{
		printf("Attempted to load Environment from malformed xml file");
		return;
	}

	curNode = curNode.first_child();

	char* curName = (char*) curNode.name();

	while (strcmp(curName, ""))
	{
		if (!strcmp(curName, "name"))
		{
			name = curNode.first_child().value();
		}

		else if (!strcmp(curName, "Room"))
		{
			Room* R = NULL;

			if (!strcmp(curNode.first_child().name(), "file"))
			{
				R = new Room((char*)curNode.first_child().value());
			}

			else
			{
				R = new Room(curNode);
			}

			rooms[R->name] = R;
		}

		curNode = curNode.next_sibling();
		curName = (char*) curNode.name();
	}

	if (name.empty())
	{
		printf("No environment name detected in file: %s. Consider adding a <name> node to this file\n", fileName);
		name = "Default Room";
	}

	StateManager::environments[name] = this;
}
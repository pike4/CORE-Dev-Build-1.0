#include "Environment.h"
#include "pugixml.hpp"

Environment::Environment(char* fileName)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load(fileName);

	pugi::xml_node curNode = doc.first_child().first_child();
	char* curName = (char*) curNode.name();

	while (strcmp(curName, ""))
	{
		if (!strcmp(curName, "name"))
		{
			name = curNode.value;
		}

		else if (!strcmp(curName, "room"))
		{

		}


		curNode = curNode.next_sibling();
		curName = (char*) curNode.name();
	}
}
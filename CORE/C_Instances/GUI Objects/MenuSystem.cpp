#include "pugixml.hpp"
#include "MenuSystem.h"
#include "MenuScreen.h"
#include "ObjectManager.h"
#include "StateManager.h"

MenuSystem::MenuSystem(char* fileName)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(fileName);

	pugi::xml_node cur = doc.first_child().first_child();
	name = new char;
	//name = (char*)cur.first_child().value();
	menus = *(new std::map<std::string, MenuScreen*>);

	while (strcmp(cur.name(), ""))
	{
		if (!strcmp(cur.name(), "name"))
		{
			name = cur.first_child().value();
		}

		else if (!strcmp(cur.name(), "MenuScreen"))
		{
			MenuScreen* MS = new MenuScreen(cur, this);
			if (MS != NULL)
			{
				menus[MS->name] = MS;
			}
		}

		cur = cur.next_sibling();
	}

	if (name.empty())
	{
		name = "DEFAULT";
	}

	StateManager::menuSystems[name] = this;
	
}
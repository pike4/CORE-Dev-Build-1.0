#include "pugixml.hpp"
#include "MenuSystem.h"
#include "MenuScreen.h"
#include "ObjectManager.h"
#include "StateManager.h"

MenuSystem::MenuSystem(std::string fileName)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(fileName.c_str());

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

MenuScreen* MenuSystem::getMenuScreen(std::string name)
{
	if (menus.find(name) != menus.end())
	{
		return menus[name];
	}

	else
	{
		//TODO: log error
		return NULL;
	}
}

void MenuSystem::goToMenuScreen(std::string name)
{
	if (menus.find(name) != menus.end())
	{
		MenuScreen* newLayer = menus[name];
		StateManager::addMenuScreenLayer(newLayer);
	}

	else
	{
		//TODO log error
	}
}
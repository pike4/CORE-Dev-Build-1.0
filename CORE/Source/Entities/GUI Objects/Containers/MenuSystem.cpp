#include "MenuSystem.h"
#include "MenuScreen.h"

#include "CORE_Resources.h"
#include "CORE_Factory.h"
#include "CORE.h"

MenuSystem::MenuSystem(std::string fileName) 
	: MenuSystem(CORE_Resources::getFirstNodeFromFile(fileName))
{}

MenuSystem::MenuSystem(XMLNode def)
{
	menus = *(new std::map<std::string, MenuScreen*>);
	name = def.getVariable("name");

	XMLNode screenChild = def.getChild("menuScreens");
	
	std::vector<XMLNode> childVector = screenChild.getChildren();
	std::vector<XMLNode> menuVector = def.getChildren({ "children", "name" });

	menuVector.insert(menuVector.end(), childVector.begin(), childVector.end());

	for (int i = 0; i < menuVector.size(); i++)
	{
		XMLNode cur = menuVector[i];
		MenuScreen* newMenu = new MenuScreen(cur);

		if (newMenu)
		{
			newMenu->finalize();
			menus[cur.getVariable("name")] = newMenu;
		}
	}

	if (name.empty())
	{
		// Log error
		name = "DEFAULT";
	}

	CORE_Resources::menuSystems[name] = this;
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
		CORE::addMenuScreenLayer(newLayer);
	}

	else
	{
		//TODO log error
	}
}
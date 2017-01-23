#include "MenuSystem.h"
#include "MenuScreen.h"

#include "CORE_Resources.h"
#include "CORE_Factory.h"
#include "CORE.h"

MenuSystem::MenuSystem(std::string fileName) 
	: MenuSystem(CORE_Resources::getFirstNodeFromFile(fileName))
{}

MenuSystem::MenuSystem(Definer* def)
{
	menus = *(new std::map<std::string, MenuScreen*>);
	name = def->getVariable("name");

	Definer* screenChild = def->getChild("menuScreens");
	
	std::vector<Definer*>* menuVector = screenChild->getChildren();

	for (int i = 0; i < menuVector->size(); i++)
	{
		Definer* cur = (*menuVector)[i];
		MenuScreen* newMenu = new MenuScreen(cur);

		if (newMenu)
		{
			newMenu->registerSelf(NULL);
			menus[cur->getVariable("name")] = newMenu;
		}
	}

	if (name.empty())
	{
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
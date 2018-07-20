#include "MenuSystem.h"
#include "MenuScreen.h"

#include "CORE_Resources.h"
#include "CORE_Factory.h"
#include "CORE.h"

MenuSystem::MenuSystem(std::string fileName) 
	: MenuSystem(CORE_Resources::getFirstNodeFromFile(fileName))
{}

MenuSystem::MenuSystem(Node* def)
{
	menus = *(new std::map<std::string, MenuScreen*>);
	name = def->getVariable("name");

	Node* screenChild = (Node*) def->getChild("menuScreens");
	
	std::vector<Node*>* menuVector = (std::vector<Node*>*) screenChild->getChildren();

	for (unsigned int i = 0; i < menuVector->size(); i++)
	{
		Node* cur = (*menuVector)[i];
		MenuScreen* newMenu = new MenuScreen(cur);

		if (newMenu)
		{
			newMenu->finalize();
			menus[cur->getVariable("name")] = newMenu;
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
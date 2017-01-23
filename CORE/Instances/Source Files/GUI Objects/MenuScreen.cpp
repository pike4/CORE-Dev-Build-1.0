#include "MenuScreen.h"
#include "CORE_Factory.h"
#include "pugixml.hpp"
#include "NavigationButton.h"
#include "CORE_Devices.h"
#include <vector>

MenuScreen::MenuScreen(Definer* def)
	:Entity(def)
{
	getArgsFromNode(def);
}

MenuScreen::MenuScreen(Definer* def, MenuSystem* root) : MenuScreen(def)
{
}

MenuScreen::MenuScreen(char* fileName)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(fileName);
	pugi::xml_node node = doc.first_child();

	Definer* newMenuDef = CORE_Factory::generateDefiner(node);

	if (newMenuDef->getName() == "MenuScreen")
	{
		getArgsFromNode(newMenuDef);
	}
}

void MenuScreen::getArgsFromNode(Definer* def, MenuSystem* root)
{
	getArgsFromNode(def);
}

void MenuScreen::getArgsFromNode(Definer* def)
{
	name = def->getVariable("name");

	Definer* controlsParent = def->getChild("controls");

	if (controlsParent)
	{
		std::vector<Definer*>* controlsVector = controlsParent->getChildren();

		for (unsigned int i = 0; i < controlsVector->size(); i++)
		{
			Definer* cur = (*controlsVector)[i];

			Control* newControl = NULL;
				
			if(newControl = CORE_Factory::generateControl(cur))
			{
				components.push_back(newControl);
			}
		}
	}
}

void MenuScreen::checkMousePos(int x, int y)
{
	
}

void MenuScreen::add(Control* controlsToAdd[], int numControls)
{
	for (int i = 0; i < numControls; i++)
	{
		components.push_back(controlsToAdd[i]);
	}
}

void MenuScreen::add(Control* controlToAdd)
{
	components.push_back(controlToAdd);
}

void MenuScreen::checkMouseDown(int x, int y)
{

}

void MenuScreen::checkMouseUp(int x, int y)
{

}

void MenuScreen::draw()
{
	for (unsigned int i = 0; i < components.size(); i++)
	{
		if (components[i] != NULL)
		{
			components[i]->handleInput(drawStep);
		}
	}
}

void MenuScreen::update()
{
	for (unsigned int i = 0; i < components.size(); i++)
	{
		if (components[i] != NULL)
		{
			components[i]->handleInput(updateStep);
		}
	}
}
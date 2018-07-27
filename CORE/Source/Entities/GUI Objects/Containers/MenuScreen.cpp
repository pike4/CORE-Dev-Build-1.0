#include "MenuScreen.h"
#include "CORE_Factory.h"
#include "CORE_Devices.h"

#include <vector>

MenuScreen::MenuScreen(XMLNode def)
{
	getArgsFromNode(def);
}

MenuScreen::MenuScreen(XMLNode def, MenuSystem* root) : MenuScreen(def)
{
}

MenuScreen::MenuScreen(char* fileName)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(fileName);
	pugi::xml_node node = doc.first_child();

	XMLNode newMenuDef = CORE_Factory::generateNode(node);

	if (newMenuDef.getName() == "MenuScreen")
	{
		getArgsFromNode(newMenuDef);
	}
}

void MenuScreen::getArgsFromNode(XMLNode def, MenuSystem* root)
{
	getArgsFromNode(def);
}

void MenuScreen::getArgsFromNode(XMLNode def)
{
	name = def.getVariable("name");

	XMLNode controlsParent = def.getChild("controls");

	if (!controlsParent.null())
	{
		std::vector<XMLNode> controlsVector = controlsParent.getChildren();

		for (unsigned int i = 0; i < controlsVector.size(); i++)
		{
			XMLNode cur = controlsVector[i];

			Component* newControl = NULL;
				
			if(newControl = CORE_Factory::generateObject(cur))
			{
				components.push_back(newControl);
				newControl->registerEv(this);
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
			components[i]->handle(drawStep);
		}
	}

	if (observers.find(drawStep) != observers.end())
	{
		std::vector<Controllable*>& vec = observers[drawStep];
		for (int i = 0; i < vec.size(); i++)
		{
			vec[i]->handle(drawStep);
		}
	}
}

void MenuScreen::update()
{
	for (unsigned int i = 0; i < components.size(); i++)
	{
		if (components[i] != NULL)
		{
			components[i]->handle(updateStep);
		}
	}
}
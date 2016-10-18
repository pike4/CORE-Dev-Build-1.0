#include "MenuScreen.h"
#include "ObjectManager.h"
#include "pugixml.hpp"
#include "NavigationButton.h"
#include "EventManager.h"
#include <vector>

MenuScreen::MenuScreen(pugi::xml_node node)
	:Entity(node)
{
	getArgsFromNode(node);
}

MenuScreen::MenuScreen(pugi::xml_node node, MenuSystem* root) : MenuScreen(node)
{
}

MenuScreen::MenuScreen(char* fileName)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(fileName);
	pugi::xml_node node = doc.first_child();

	if (!strcmp("MenuScreen", node.name()))
	{
		getArgsFromNode(node);
	}
}

void MenuScreen::getArgsFromNode(pugi::xml_node node, MenuSystem* root)
{
	pugi::xml_node curNode = node.first_child();

	char* curName = (char*)curNode.name();

	while (strcmp(curNode.name(), ""))
	{
		if (!strcmp(curName, "name"))
		{
			name = (char*)curNode.first_child().value();
		}

		else if (!strcmp(curName, "controls"))
		{
			pugi::xml_node controlNode = curNode.first_child();

			while (strcmp("", controlNode.name()))
			{
				Control* newControl = ObjectManager::generateControl(controlNode.name(), controlNode);
				
				if (newControl)
				{
					controls.push_back(newControl);
				}
				controlNode = controlNode.next_sibling();
			}
		}

		curNode = curNode.next_sibling();
		curName = (char*)curNode.name();
	}
}

void MenuScreen::getArgsFromNode(pugi::xml_node node)
{
	pugi::xml_node curNode = node.first_child();
	char* curName = (char*) curNode.name();
	
	while (strcmp(curNode.name(), "") != 0)
	{
		if (!strcmp(curNode.name(), "name"))
		{
			name = curNode.first_child().value();
		}

		else if (!strcmp(curName, "Controls"))
		{
			pugi::xml_node controlNode = curNode.first_child();

			while (strcmp("", controlNode.name()))
			{
				Control* newControl = ObjectManager::generateControl(controlNode.name(), controlNode);

				if (newControl)
				{
					controls.push_back(newControl);
				}
				controlNode = controlNode.next_sibling();
			}
		}

		curNode = curNode.next_sibling();
		curName = (char*) curNode.name();
	} 
}

void MenuScreen::checkMousePos(int x, int y)
{
	
}

void MenuScreen::add(Control* controlsToAdd[], int numControls)
{
	for (int i = 0; i < numControls; i++)
	{
		controls.push_back(controls[i]);
	}
}

void MenuScreen::add(Control* controlToAdd)
{
	controls.push_back(controlToAdd);
}

void MenuScreen::checkMouseDown(int x, int y)
{

}

void MenuScreen::checkMouseUp(int x, int y)
{

}

void MenuScreen::handleInput(int key, int upDown, int x, int y)
{
	for (int i = 0; i < controls.size(); i++)
	{
		if (controls[i] != NULL)
		{
			controls[i]->handleInput(key, upDown, x, y);
		}
	}
}

void MenuScreen::draw(SDL_Renderer* renderer)
{
	for (int i = 0; i < controls.size(); i++)
	{
		if (controls[i] != NULL)
		{
			controls[i]->handleInput(drawStep);
		}
	}
}

void MenuScreen::update()
{
	for (int i = 0; i < controls.size(); i++)
	{
		if (controls[i] != NULL)
		{
			controls[i]->handleInput(updateStep);
		}
	}
}
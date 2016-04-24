#include "MenuScreen.h"
#include "ObjectManager.h"
#include "pugixml.hpp"
#include "NavigationButton.h"
#include <vector>

MenuScreen::MenuScreen()
{
	//buttons = std::vector();
}

MenuScreen::MenuScreen(pugi::xml_node node)
{
	getArgsFromNode(node);
}

MenuScreen::MenuScreen(pugi::xml_node node, MenuSystem* root)
{
	getArgsFromNode(node, root);
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

	while (strcmp(curNode.name(), "") != 0)
	{


		if (!strcmp(curName, "name"))
		{
			name = (char*)curNode.first_child().value();
		}

		else if (strcmp(curName, "button") == 0)
		{
			buttons.push_back(new Button(curNode));
		}

		else if (!strcmp(curName, "NavigationButton"))
		{
			buttons.push_back(new NavigationButton(curNode, root));
		}

		else if (strcmp(curName, "background") == 0)
		{

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


		if (!strcmp(curName, "name"))
		{
			name = (char*)curNode.first_child().value();
		}

		else if (strcmp(curName, "button") == 0)
		{
			buttons.push_back(new Button(curNode));
		}

		else if (strcmp(curName, "background") == 0)
		{

		}

		curNode = curNode.next_sibling();
		curName = (char*) curNode.name();
	} 
}

void MenuScreen::checkMousePos()
{
	if (ObjectManager::currentGUI != NULL)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];

			if (button->isWithin(x, y))
			{
				button->mouseHover();
			}

			else
			{
				button->mouseLeave();
			}
		}
	}
}

void MenuScreen::add(Button* buttonsToAdd[], int numButtons)
{
	for (int i = 0; i < numButtons; i++)
	{
		buttons.push_back(buttonsToAdd[i]);
	}
}

void MenuScreen::add(Button* buttonToAdd)
{
		buttons.push_back(buttonToAdd);
}

void MenuScreen::checkMouseDown()
{
	if (ObjectManager::currentGUI != NULL)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);

		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];

			if (button->isWithin(x, y))
			{
				button->mouseDown();
			}

		}
	}
}

void MenuScreen::checkMouseUp()
{
	if (ObjectManager::currentGUI != NULL)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];

			if (button->isWithin(x, y))
			{
				button->mouseUp();
			}
		}
	}
}
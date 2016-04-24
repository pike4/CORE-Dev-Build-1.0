#pragma once
#include "Button.h"
#include "MenuSystem.h"
#include <vector>

class MenuScreen
{
public:

	MenuScreen();

	MenuScreen(pugi::xml_node node);
	MenuScreen(pugi::xml_node node, MenuSystem* root);
	MenuScreen(char* fileName);

	std::vector<Button*> buttons;

	std::string name;

	void checkMousePos();
	void checkMouseDown();
	void checkMouseUp();

	void add(Button* buttonsToAdd[], int numButtons);
	void add(Button* buttonToAdd);

private:
	void getArgsFromNode(pugi::xml_node node);
	void getArgsFromNode(pugi::xml_node node, MenuSystem* root);

};
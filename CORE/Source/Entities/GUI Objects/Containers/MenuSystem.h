#pragma once
#include "Node.h"

#include <map>

class MenuScreen;

class MenuSystem
{
public:
	std::map<std::string, MenuScreen*> menus;
	std::string name;

	MenuSystem(std::string fileName);
	MenuSystem(Node def);

	MenuScreen* getMenuScreen(std::string name);

	void goToMenuScreen(std::string name);
};
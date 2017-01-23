#pragma once
#include "Definer.h"

#include <map>

class MenuScreen;

class MenuSystem
{
public:
	std::map<std::string, MenuScreen*> menus;
	std::string name;

	MenuSystem(std::string fileName);
	MenuSystem(Definer* def);

	MenuScreen* getMenuScreen(std::string name);

	void goToMenuScreen(std::string name);
};
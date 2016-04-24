#pragma once
#include <map>

class MenuScreen;

class MenuSystem
{
public:
	std::map<std::string, MenuScreen*> menus;
	std::string name;

	MenuSystem(char* fileName);
};
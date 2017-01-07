#pragma once
#include "ButtonComponent.h"
#include "pugixml.hpp"

class MenuDestination : public Component
{
public:
	MenuDestination();
	MenuDestination(pugi::xml_node node);
	virtual void handleInput(int key, int upDown = 0, int x = 0, int y = 0);

protected:
	std::string destination;
};
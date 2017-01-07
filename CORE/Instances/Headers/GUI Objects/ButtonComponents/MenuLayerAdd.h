#pragma once
#include "Component.h"
#include "pugixml.hpp"

class MenuLayerAdd : public Component
{
public:
	MenuLayerAdd();
	MenuLayerAdd(pugi::xml_node node);
	virtual void handleInput(int key, int upDown = 0, int x = 0, int y = 0);

protected:
	std::string source;
};
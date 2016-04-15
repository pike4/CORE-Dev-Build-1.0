#pragma once
#include "pugixml.hpp"
class BaseObject
{
public:
	int x, y;

	BaseObject(int x, int y);
	BaseObject(pugi::xml_node);
};
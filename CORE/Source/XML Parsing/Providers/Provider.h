#pragma once

#include <string>
#include "pugixml.hpp"

class Provider
{
public:
	virtual std::string getValue(pugi::xml_node node) = 0;
};
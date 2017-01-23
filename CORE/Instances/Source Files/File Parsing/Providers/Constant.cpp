#include "Constant.h"
#include <string>
#include "pugixml.hpp"

Constant::Constant(std::string newValue)
{
	value = newValue;
}

std::string Constant::getValue(pugi::xml_node node)
{
	return value;
}
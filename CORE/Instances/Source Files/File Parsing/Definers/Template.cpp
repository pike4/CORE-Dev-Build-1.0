#include "Definer.h"
#include "Constant.h"
#include "TemplateDef.h"

#include "pugixml.hpp"

Template::Template(pugi::xml_node myNode, TemplateDef* definition)
{
	node = *(new pugi::xml_node(myNode));
	def = definition;
}

std::string Template::getVariable(std::string name)
{
	return def->getVariable(node, name);
}

std::string Template::getName()
{
	return def->surname;
}
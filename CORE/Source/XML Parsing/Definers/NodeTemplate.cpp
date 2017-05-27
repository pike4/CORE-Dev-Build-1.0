#include "Node.h"
#include "Constant.h"
#include "NodeTemplate.h"
#include "TemplateDef.h"

#include "pugixml.hpp"

NodeTemplate::NodeTemplate(pugi::xml_node myNode, TemplateDef* definition)
{
	node = *(new pugi::xml_node(myNode));
	def = definition;
}

std::string NodeTemplate::getVariable(std::string name)
{
	return def->getVariable(node, name);
}

std::string NodeTemplate::getName()
{
	return def->surname;
}
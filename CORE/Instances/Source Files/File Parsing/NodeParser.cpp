#include "Definer.h"

NodeParser::NodeParser(pugi::xml_node node)
{
	myNode = node;
}

std::string NodeParser::getVariable(pugi::xml_node node, std::string name)
{
	return node.child(name.c_str()).first_child.value();
}
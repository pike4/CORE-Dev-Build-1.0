#include "Definer.h"

NodeParser::NodeParser(pugi::xml_node myNode)
{
	node = myNode;
}

std::string NodeParser::getVariable(std::string name)
{
	std::string ret = "0";
	pugi::xml_node child = node.child(name.c_str());

	if (child)
	{
		child = child.first_child();
		if (child)
		{
			ret = child.value();
		}
	}

	return ret;
}
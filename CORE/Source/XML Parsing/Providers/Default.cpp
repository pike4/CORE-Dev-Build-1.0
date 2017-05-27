#include "Default.h"

Default::Default(std::string newName, std::string newValue)
{
	name = newName;
	value = newValue;
}

std::string Default::getValue(pugi::xml_node node)
{
	pugi::xml_node child = node.child(name.c_str());

	if (child)
	{
		child = child.first_child();

		if (child)
		{
			return child.value();
		}
	}

	return value;
}
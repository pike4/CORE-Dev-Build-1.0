#pragma once
#include "Provider.h"

class Variable : public Provider
{
public:
	Variable(std::string newName)
	{
		name = newName;
	}

	virtual std::string getValue(pugi::xml_node node)
	{
		return node.child(name.c_str()).first_child().value();
	}

protected:
	std::string name;
};
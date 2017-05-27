#pragma once
#include "Provider.h"

class NodeMain : public Provider
{
public:
	virtual std::string getValue(pugi::xml_node node)
	{
		return node.first_child().value();
	}
};
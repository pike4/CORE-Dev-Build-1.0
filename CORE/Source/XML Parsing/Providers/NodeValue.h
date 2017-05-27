#pragma once
#include "Provider.h"

class NodeValue : public Provider
{
public:
	virtual std::string getValue(pugi::xml_node node)
	{
		return node.value();
	}
};
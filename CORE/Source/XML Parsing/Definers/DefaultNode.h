#pragma once
#include "Node.h"

class DefaultNode : public Node
{
public:
	DefaultNode(pugi::xml_node myNode);

	virtual std::string getVariable(std::string name);

protected:
};
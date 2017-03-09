#pragma once

#include "Node.h"

class NodeTemplate : public Node
{
public:
	NodeTemplate(pugi::xml_node node, TemplateDef* definition);

	virtual std::string getVariable(std::string name);
	virtual std::string getName();

protected:
	TemplateDef* def;
};
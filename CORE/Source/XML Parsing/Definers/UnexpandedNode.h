#pragma once

#include "Node.h"
#include "Provider.h"
#include "DefaultNode.h"
#include <vector>

class UnexpandedNode
{
public:
	std::string name;
	UnexpandedNode(pugi::xml_node node, TemplateDef* temp);
	UnexpandedNode();

	// TODO implement expansions
	DefaultNode expand(pugi::xml_node node);

private:
    void readNode(pugi::xml_node);
    TemplateDef* templateDef;

    std::vector<std::pair<std::string, Provider*>> attributes;
    std::vector<UnexpandedNode> children;
	Provider* mainValue;
};
#pragma once

#include "Node.h"
#include "Provider.h"
#include <vector>

class UnexpandedNode
{
public:
	std::string name;
	UnexpandedNode(pugi::xml_node node);

	Node* expand();

private:
	std::vector<std::pair<std::string, Provider*>> attributes;
	std::vector<UnexpandedNode> children;

};
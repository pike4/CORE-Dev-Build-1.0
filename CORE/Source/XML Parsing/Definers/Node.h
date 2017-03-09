#pragma once
#include "Provider.h"

#include <string>
#include <map>
#include <vector>
#include "pugixml.hpp"

class TemplateDef;

class Node
{
	friend class TemplateDef;

public:
	virtual std::string getVariable(std::string name) = 0;
	virtual Node* getChild(std::string name);
	virtual std::vector<Node*>* getChildren();
	virtual std::string getName();
	virtual std::string getMainValue();

	//TODO: getMainValue() - return the top node value of the node, "" by default
	//TODO: getAttribute(std::string name) - return the attribute of the given name

protected:
	pugi::xml_node node;
};
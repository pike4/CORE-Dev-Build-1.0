#pragma once
#include "Provider.h"

#include <string>
#include <map>
#include <vector>
#include "pugixml.hpp"

class TemplateDef;

/*
   A simple "black box" XML node

   Purpose:
      1. Define the contents of a single XML node without revealing specifically how those contents are
         laid out internally
      2. Allow access to internal variables and child nodes by name
      3. 
*/

class Node
{
	friend class TemplateDef;

public:
	virtual std::string getVariable(std::string name) = 0;
	virtual Node* getChild(std::string name);
	virtual std::vector<Node*>* getChildren();
	virtual std::string getName() = 0;
	virtual std::string getMainValue() = 0;

	//TODO: getMainValue() - return the top node value of the node, "" by default
	//TODO: getAttribute(std::string name) - return the attribute of the given name

protected:
	pugi::xml_node node;
};
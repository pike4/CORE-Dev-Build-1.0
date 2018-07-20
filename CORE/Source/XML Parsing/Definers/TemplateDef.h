#pragma once
#include "Node.h"
#include "Provider.h"
#include "Default.h"
#include "NodeValue.h"
#include "NodeMain.h"
#include "Variable.h"
#include "Constant.h"
#include "Node.h"

#include "UnexpandedNode.h"

#include "pugixml.hpp"

#include <map>
#include <string>
#include <sstream>
#include <iostream>

struct StringAddress
{
	std::string varName;
	int index;
};

class TemplateDef
{
public:
	TemplateDef(Node* def);
	std::string getVariable(pugi::xml_node node, std::string name);
	StringAddress getAddress(std::string name);

	Node invoke(pugi::xml_node invoker);
	
	//Name used to refer to this template
	std::string name;

	//Name of the type that this template is used to stand for
	std::string surname;

protected:
	std::map<std::string, Provider*> variables;

	std::map<std::string, StringAddress> addresses;

	UnexpandedNode definer;
};

std::vector<std::string> tokenize(std::string src, char delim);
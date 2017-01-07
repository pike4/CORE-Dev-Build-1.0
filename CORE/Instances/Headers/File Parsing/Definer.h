#pragma once
#include "Definer.h"
#include "Provider.h"

#include <string>
#include <map>
#include "pugixml.hpp"

class Definer
{
public:
	virtual std::string getVariable(pugi::xml_node node, std::string name) = 0;
};

class Template : public Definer
{
public:
	Template(pugi::xml_node);

	virtual std::string getVariable(pugi::xml_node node, std::string name);

protected:
	std::map<std::string, Provider*> variables;

	std::string name;
};

class NodeParser : public Definer
{
public:
	NodeParser(pugi::xml_node node);

	virtual std::string getVariable(pugi::xml_node node, std::string name);

protected:
	pugi::xml_node myNode;
};
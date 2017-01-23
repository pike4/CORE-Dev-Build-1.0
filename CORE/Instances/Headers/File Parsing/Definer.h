#pragma once
#include "Provider.h"

#include <string>
#include <map>
#include <vector>
#include "pugixml.hpp"

class TemplateDef;

class Definer
{
	friend class TemplateDef;

public:
	virtual std::string getVariable(std::string name) = 0;
	virtual Definer* getChild(std::string name);
	virtual std::vector<Definer*>* getChildren();
	virtual std::string getName();

	//TODO: getMainValue() - return the top node value of the node, "" by default
	//TODO: getAttribute(std::string name) - return the attribute of the given name

protected:
	pugi::xml_node node;
};

class Template : public Definer
{
public:
	Template(pugi::xml_node node, TemplateDef* definition);

	virtual std::string getVariable(std::string name);
	virtual std::string getName();

protected:
	TemplateDef* def;
};

class NodeParser : public Definer
{
public:
	NodeParser(pugi::xml_node myNode);

	virtual std::string getVariable(std::string name);

protected:
};
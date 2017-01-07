#pragma once

#include <string>
#include "pugixml.hpp"

class Provider
{
public:
	virtual std::string getValue(pugi::xml_node node) = 0;
};

class NodeMain : public Provider
{
public:
	virtual std::string getValue(pugi::xml_node node)
	{
		return node.first_child.value();
	}
};

class NodeValue : public Provider
{
public:
	virtual std::string getValue(pugi::xml_node node)
	{
		return node.value();
	}
};

class Variable : public Provider
{
public:
	Variable(std::string newName)
	{
		name = newName;
	}
	
	virtual std::string getValue(pugi::xml_node node)
	{
		return node.child(name.c_str()).first_child.value();
	}

protected:
	std::string name;
};

class Constant : public Provider
{
public:
	Constant(std::string newValue);

	virtual std::string getValue(pugi::xml_node node);

protected:
	std::string value;
};
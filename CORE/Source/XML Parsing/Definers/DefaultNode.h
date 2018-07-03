#pragma once
#include "Node.h"

class DefaultNode : public Node
{
public:
	DefaultNode(pugi::xml_node myNode);
	DefaultNode();

	void readAttributes(pugi::xml_node myNode);
	void readChildren(pugi::xml_node myNode);

	virtual std::string getVariable(std::string name);

	virtual std::string getName();
	virtual std::string getMainValue();

	void addChild(DefaultNode child);
	void addAttribute(std::string name, std::string value);
	void setValue(std::string value);

protected:

	std::map<std::string, DefaultNode> children;
	std::map<std::string, std::string> attributes;
	std::string value;
	std::string name;
};
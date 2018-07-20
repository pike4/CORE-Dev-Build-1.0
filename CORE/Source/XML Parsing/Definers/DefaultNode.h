#pragma once
#include <string>
#include <vector>
#include <map>

#include "pugixml.hpp"

class DefaultNode
{
public:
	DefaultNode(pugi::xml_node myNode);
	DefaultNode();

	void readAttributes(pugi::xml_node myNode);
	void readChildren(pugi::xml_node myNode);

	virtual std::string getVariable(std::string name);

	virtual std::string getName();
	virtual std::string getMainValue();

	virtual DefaultNode* getChild(std::string name);
	virtual std::vector<DefaultNode*>* getChildren();

	void addChild(DefaultNode child);
	void addAttribute(std::string name, std::string value);
	void setValue(std::string value);
	void setName(std::string name);


	pugi::xml_node node;

protected:

	std::vector<DefaultNode> children;
	std::map<std::string, std::string> attributes;
	std::string value;
	std::string name;

};
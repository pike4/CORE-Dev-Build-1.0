#pragma once
#include <string>
#include <vector>
#include <map>

#include "pugixml.hpp"

class Node
{
public:
	Node(pugi::xml_node myNode);
	Node();

	void readAttributes(pugi::xml_node myNode);
	void readChildren(pugi::xml_node myNode);

	virtual std::string getVariable(std::string name);

	virtual std::string getName();
	virtual std::string getMainValue();

	virtual Node* getChild(std::string name);
	virtual std::vector<Node*> getChildren();

	void addChild(Node child);
	void addAttribute(std::string name, std::string value);
	void setValue(std::string value);
	void setName(std::string name);

	bool null();


	pugi::xml_node node;

protected:
	std::vector<Node> children;
	std::map<std::string, std::string> attributes;
	std::string value;
	std::string name;

	bool isNull;
};
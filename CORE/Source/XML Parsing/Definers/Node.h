#pragma once
#include <string>
#include <vector>
#include <map>

#include "pugixml.hpp"

class XMLNode
{
public:
	XMLNode(pugi::xml_node myNode);
	XMLNode();

	void	readAttributes(pugi::xml_node myNode);
	void	readChildren(pugi::xml_node myNode);

	virtual	std::string getVariable(std::string name);

	virtual	std::string getName();
	virtual	std::string getMainValue();

	virtual	XMLNode getChild(std::string name);
	virtual	std::vector<XMLNode> getChildren();

	void	addChild(XMLNode child);
	void	addAttribute(std::string name, std::string value);
	void	setValue(std::string value);
	void	setName(std::string name);

	bool	null();
	void	setNull(bool n);


	pugi::xml_node node;

protected:
	std::vector<XMLNode> children;
	std::map<std::string, std::string> attributes;
	std::string value;
	std::string name;

	bool isNull;
};
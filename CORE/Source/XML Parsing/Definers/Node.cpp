#include "Node.h"
#include "Node.h"

#include "CORE_Resources.h"
#include "CORE_Factory.h"

XMLNode::XMLNode() {
	isNull = true;
}

XMLNode::XMLNode(pugi::xml_node myNode)
{
	isNull = false;
	node = myNode;
	name = node.name();
	readAttributes(myNode);
	readChildren(myNode);

	if (children.size() == 0)
	{
		value = myNode.first_child().value();
	}
}

void XMLNode::readAttributes(pugi::xml_node myNode)
{
	pugi::xml_attribute attr = myNode.first_attribute();

	while (attr.name() != "")
	{
		addAttribute(attr.name(), attr.value());
		attr = attr.next_attribute();
	}
}

void XMLNode::readChildren(pugi::xml_node myNode)
{
	pugi::xml_node child = myNode.first_child();

	while (child.name() != "")
	{
		addChild(CORE_Factory::generateNode(child));
		child = child.next_sibling();
	}
}

std::string XMLNode::getVariable(std::string name)
{
	std::string ret = "0";

	bool found = false;

	if ( attributes.find(name) != attributes.end() )
	{
		ret = attributes[name];
		found = true;
	}

	if ( !found )
	{
		XMLNode child = getChild(name);

		if ( !child.null() )
		{
			XMLNode d = child;
			ret = d.getMainValue();
		}
	}

	if ( !ret.empty() && ret[0] == '$' )
	{
		ret = CORE_Resources::resolveVariable(ret);
	}

	return ret;
}

std::string XMLNode::getName()
{
	return name;
}

std::string XMLNode::getMainValue()
{
	return value;
}

void XMLNode::addChild(XMLNode child)
{
	children.push_back(child);
}

void XMLNode::addAttribute(std::string name, std::string value)
{
	attributes[name] = value;
}

void XMLNode::setValue(std::string val)
{
	value = val;
}

void XMLNode::setName(std::string newName)
{
	name = newName;
}

XMLNode XMLNode::getChild(std::string name)
{
	XMLNode ret;

	for (unsigned int i = 0; i < children.size(); i++)
	{
		if (children[i].getName() == name)
		{
			ret = children[i];
			break;
		}
	}

	return ret;
}

std::vector<XMLNode> XMLNode::getChildren()
{
	std::vector<XMLNode> ret;

	for (unsigned int i = 0; i < children.size(); i++)
	{
		ret.push_back(children[i]);
	}

	return ret;
}

bool XMLNode::null()
{
	return isNull;
}

void XMLNode::setNull(bool n)
{
	isNull = n;
}
#include "Node.h"
#include "DefaultNode.h"

#include "CORE_Resources.h"

DefaultNode::DefaultNode() {}

DefaultNode::DefaultNode(pugi::xml_node myNode)
{
	node = myNode;
	name = node.name();
	readAttributes(myNode);
	readChildren(myNode);

	if (children.size() == 0)
	{
		value = myNode.first_child().value();
	}
}

void DefaultNode::readAttributes(pugi::xml_node myNode)
{
	pugi::xml_attribute attr = myNode.first_attribute();

	while (attr.name() != "")
	{
		addAttribute(attr.name(), attr.value());
		attr = attr.next_attribute();
	}
}

void DefaultNode::readChildren(pugi::xml_node myNode)
{
	pugi::xml_node child = myNode.first_child();

	while (child.name() != "")
	{
		addChild(DefaultNode(child));
		child = child.next_sibling();
	}
}

std::string DefaultNode::getVariable(std::string name)
{
	std::string ret = "0";

	bool found = false;

	pugi::xml_attribute searchAttribute = node.attribute(name.c_str());

	if (searchAttribute)
	{
		ret = searchAttribute.value();
		found = true;
	}

	if (!found)
	{
		pugi::xml_node child = node.child(name.c_str());

		if (child != NULL)
		{
			child = child.first_child();
			if (child != NULL)
			{
				ret = child.value();
				found = true;
			}
		}
	}

	if (ret[0] == '$')
	{
		ret = CORE_Resources::resolveVariable(ret);
	}

	return ret;
}

std::string DefaultNode::getName()
{
	return name;
}

std::string DefaultNode::getMainValue()
{
	return value;
}

void DefaultNode::addChild(DefaultNode child)
{
	children[child.getName()] = child;
}

void DefaultNode::addAttribute(std::string name, std::string value)
{
	attributes[name] = value;
}

void DefaultNode::setValue(std::string val)
{
	value = val;
}
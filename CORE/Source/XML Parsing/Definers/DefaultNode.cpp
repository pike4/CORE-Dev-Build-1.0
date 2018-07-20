#include "DefaultNode.h"
#include "DefaultNode.h"

#include "CORE_Resources.h"
#include "CORE_Factory.h"

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
		addChild(*CORE_Factory::generateNode(child));
		child = child.next_sibling();
	}
}

std::string DefaultNode::getVariable(std::string name)
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
		DefaultNode* child = (DefaultNode*) getChild(name);

		if ( child )
		{
			DefaultNode* d = (DefaultNode*) child;
			ret = d->getMainValue();
		}
	}

	if ( !ret.empty() && ret[0] == '$' )
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
	children.push_back(child);
}

void DefaultNode::addAttribute(std::string name, std::string value)
{
	attributes[name] = value;
}

void DefaultNode::setValue(std::string val)
{
	value = val;
}

void DefaultNode::setName(std::string newName)
{
	name = newName;
}

DefaultNode* DefaultNode::getChild(std::string name)
{
	DefaultNode* ret = NULL;

	for (unsigned int i = 0; i < children.size(); i++)
	{
		if (children[i].getName() == name)
		{
			ret = &children[i];
			break;
		}
	}

	return ret;
}

std::vector<DefaultNode*>* DefaultNode::getChildren()
{
	std::vector<DefaultNode*>* ret = new std::vector<DefaultNode*>();

	for (unsigned int i = 0; i < children.size(); i++)
	{
		ret->push_back(&children[i]);
	}

	return ret;
}

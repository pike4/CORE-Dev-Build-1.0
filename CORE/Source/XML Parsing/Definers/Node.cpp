#include "Node.h"
#include "Node.h"

#include "CORE_Resources.h"
#include "CORE_Factory.h"

Node::Node() {}

Node::Node(pugi::xml_node myNode)
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

void Node::readAttributes(pugi::xml_node myNode)
{
	pugi::xml_attribute attr = myNode.first_attribute();

	while (attr.name() != "")
	{
		addAttribute(attr.name(), attr.value());
		attr = attr.next_attribute();
	}
}

void Node::readChildren(pugi::xml_node myNode)
{
	pugi::xml_node child = myNode.first_child();

	while (child.name() != "")
	{
		addChild(*CORE_Factory::generateNode(child));
		child = child.next_sibling();
	}
}

std::string Node::getVariable(std::string name)
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
		Node* child = getChild(name);

		if ( child )
		{
			Node* d = child;
			ret = d->getMainValue();
		}
	}

	if ( !ret.empty() && ret[0] == '$' )
	{
		ret = CORE_Resources::resolveVariable(ret);
	}

	return ret;
}

std::string Node::getName()
{
	return name;
}

std::string Node::getMainValue()
{
	return value;
}

void Node::addChild(Node child)
{
	children.push_back(child);
}

void Node::addAttribute(std::string name, std::string value)
{
	attributes[name] = value;
}

void Node::setValue(std::string val)
{
	value = val;
}

void Node::setName(std::string newName)
{
	name = newName;
}

Node* Node::getChild(std::string name)
{
	Node* ret = NULL;

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

std::vector<Node*> Node::getChildren()
{
	std::vector<Node*> ret;

	for (unsigned int i = 0; i < children.size(); i++)
	{
		ret.push_back(&children[i]);
	}

	return ret;
}

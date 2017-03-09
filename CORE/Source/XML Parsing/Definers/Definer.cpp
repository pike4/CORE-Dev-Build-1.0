#include "Node.h"
#include "CORE_Factory.h"

#include <string>

//Return a vector of allocated definers 
std::vector<Node*>* Node::getChildren()
{
	std::vector<Node*>* ret = new std::vector<Node*>;
	pugi::xml_node cur = node.first_child();

	while (cur)
	{
		ret->push_back(CORE_Factory::generateNode(cur));
		cur = cur.next_sibling();
	}

	return ret;
}

//Return an allocated definer for a child node of the given name, NULL if it does not exist
Node* Node::getChild(std::string name)
{
	Node* ret = NULL;
	pugi::xml_node child = node.child(name.c_str());

	if (child)
	{
		ret = CORE_Factory::generateNode(child);
	}

	return ret;
}

std::string Node::getName()
{
	return node.name();
}

std::string Node::getMainValue()
{
	return node.first_child().value();
}
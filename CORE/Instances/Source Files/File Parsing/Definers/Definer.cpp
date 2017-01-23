#include "Definer.h"
#include "CORE_Factory.h"
#include <string>

//Return a vector of allocated definers 
std::vector<Definer*>* Definer::getChildren()
{
	std::vector<Definer*>* ret = new std::vector<Definer*>;
	pugi::xml_node cur = node.first_child();

	while (cur)
	{
		ret->push_back(CORE_Factory::generateDefiner(cur));
		cur = cur.next_sibling();
	}

	return ret;
}

//Return an allocated definer for a child node of the given name, NULL if it does not exist
Definer* Definer::getChild(std::string name)
{
	Definer* ret = NULL;
	pugi::xml_node child = node.child(name.c_str());

	if (child)
	{
		ret = CORE_Factory::generateDefiner(child);
	}

	return ret;
}

std::string Definer::getName()
{
	return node.name();
}
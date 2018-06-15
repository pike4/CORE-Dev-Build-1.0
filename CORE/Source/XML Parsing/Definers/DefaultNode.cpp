#include "Node.h"
#include "DefaultNode.h"

#include "CORE_Resources.h"

DefaultNode::DefaultNode(pugi::xml_node myNode)
{
	node = myNode;
}

std::string DefaultNode::getVariable(std::string name)
{
	std::string ret = "0";
	pugi::xml_node child = node.child(name.c_str());

	bool found = false;

	if (child)
	{
		child = child.first_child();
		if (child)
		{
			ret = child.value();
			found = true;
		}
	}

	if (!found)
	{
		pugi::xml_attribute searchAttribute = node.attribute(name.c_str());

		if (searchAttribute)
		{
			ret = searchAttribute.value();
		}
	}

   if (ret[0] == '$')
   {
       ret = CORE_Resources::resolveVariable(ret);
   }

	return ret;
}
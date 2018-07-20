#include "TemplateDef.h"
#include "Node.h"
#include "CORE_Resources.h"

std::vector<std::string> tokenize(std::string src, char delim)
{
	std::string cur = "";

	std::vector<std::string> ret;

	for (int i = 0; i < src.length(); i++)
	{
		if (src[i] == delim || src[i] == ' ')
		{
			ret.push_back(cur);
			cur = "";
		}

		else
		{
			cur += src.substr(i, 1);
		}
	}

	if (cur != "")
	{
		ret.push_back(cur);
	}

	return ret;
}

//node	-	pugi node that defines the form of the NodeTemplate
TemplateDef::TemplateDef(Node def)
{
    name = def.getVariable("name");
    pugi::xml_node curNode = def.node;
    pugi::xml_node sourcesNode = curNode.child("sources");
    
    pugi::xml_node sourceChild = sourcesNode.first_child();
    
    while (sourceChild.name() != "")
    {
        std::vector<std::string> vars = tokenize(sourceChild.first_child().value(), ',');
        
        for (int i = 0; i < vars.size(); i++)
        {
            addresses[vars[i]] = { sourceChild.name(), i };
        }
        
        sourceChild = sourceChild.next_sibling();
    }
    
    pugi::xml_node childNode = curNode.first_child();
    
    definer = UnexpandedNode(curNode, this);
}


// Return a string variable to the invoker node that requested it
std::string TemplateDef::getVariable(pugi::xml_node node, std::string name)
{
	std::string ret = "0";
	
	if (variables.find(name) != variables.end())
	{
		Provider* provider = variables[name];

		if (provider)
		{
			ret = provider->getValue(node);
		}
	}

	return ret;
}

StringAddress TemplateDef::getAddress(std::string name)
{
    StringAddress ret;

    if (addresses.find(name) != addresses.end())
    {
        ret = addresses[name];
    }

    return ret;
}

// Return an instance of the template given an invoker node
Node TemplateDef::invoke(pugi::xml_node invoker)
{
    return definer.expand(invoker);
}
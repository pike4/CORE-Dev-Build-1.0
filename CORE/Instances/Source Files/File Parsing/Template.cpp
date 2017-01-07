#include "Template.h"
#include "Constant.h"
#include "Variable.h"

#include "pugixml.hpp"
#include <string>
#include <sstream>
#include <iostream>

//node	-	pugi node that defines the form of the Template
Template::Template(pugi::xml_node node)
{
	name = node.value();

	pugi::xml_node curNode = node.first_child();
	std::string curName = curNode.name();

	bool hasMain = false;
	bool hasValue = false;

	while (!curName.empty())
	{
		if (curName == "components")
		{
			//Figure out how sub-components will work
		}

		// Other stuff

		else
		{
			std::string providerType = curNode.name();

			if (!providerType.empty())
			{
				if (!hasMain && providerType == "main")
				{
					hasMain = true;
					variables[curName] = new NodeMain();
				}

				else if (!hasValue && providerType == "value")
				{
					hasValue = true;
					variables[curName] = new NodeValue();
				}

				else if (providerType == "constant")
				{
					variables[curName] = new Constant(curNode.first_child().value());
				}

				else
				{
					std::stringstream inStream;
					inStream.str(providerType);

					std::string type;
					std::string aliases;

					std::getline(inStream, type, ':');
					std::getline(inStream, aliases, ':');

					//Variables in templates can be given aliases in 
					//the form below. This variable can be instantiated
					//using any of those aliases
					//eg.	-	name=variable:alias1,alias2,alias3
					if (type == "variable")
					{
						Variable* newVariable = new Variable();
						variables[curName] = newVariable;

						if (!aliases.empty())
						{
							inStream.str(aliases);

							while (std::getline(inStream, type, ','))
							{
								variables[type] = newVariable;
							}
						}
					}
				}
			}
		}
	}

}

std::string Template::getVariable(pugi::xml_node node, std::string name)
{
	return variables[name]->getValue(node);
}
#include "TemplateDef.h"
#include "CORE_Resources.h"

//node	-	pugi node that defines the form of the NodeTemplate
TemplateDef::TemplateDef(Node* def)
{
	pugi::xml_node curNode = def->node;

	if (curNode)
	{
		pugi::xml_attribute nameAttr = curNode.attribute("name");
		
		if (nameAttr)
		{
			name = nameAttr.value();
		}
	}

	curNode = def->node.first_child();
	surname = def->getName();

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
			std::string providerType = curNode.attribute("type").value();

			if (!providerType.empty())
			{
				if (!hasMain && providerType == "main")
				{
					hasMain = true;
					variables[curName] = new NodeMain();
				}

				else if (providerType == "default")
				{
                std::string value = CORE_Resources::checkVariable(curNode.first_child().value());

                variables[curName] = new Default(curName, value);
				}

				else if (!hasValue && providerType == "value")
				{
					hasValue = true;
					variables[curName] = new NodeValue();
				}

				else if (providerType == "constant")
				{
                std::string value = CORE_Resources::checkVariable(curNode.first_child().value());
					variables[curName] = new Constant(value);
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
					//eg.	-	type=variable:alias1,alias2,alias3
					if (type == "variable")
					{
						std::getline(inStream, type, ',');
						Variable* newVariable = new Variable(type);
						
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

		curNode = curNode.next_sibling();
		curName = curNode.name();
	}

}

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
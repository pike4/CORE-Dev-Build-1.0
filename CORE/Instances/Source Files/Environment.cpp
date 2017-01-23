#include "Environment.h"
#include "CORE.h"
#include "CORE_Resources.h"
#include "CORE_Factory.h"


//Get the fuck rid of this and everything else like it. Services in the namespaces should deal
//with this
Environment::Environment(std::string fileName)
{
	Definer* def = CORE_Resources::getFirstNodeFromFile(fileName);

	//If loading directly from a file, this should be defined in the first node
	if (def->getName() != "environment")
	{
		printf("Attempted to load Environment from malformed xml file");
		return;
	}

	getArgsFromNode(def);
	CORE_Resources::environments[name] = this;

	if (name.empty())
	{
		printf("No environment name detected in file: %s. Consider adding a <name> node to this file\n", fileName.c_str());
		name = "Default Environment";
	}
}

Environment::Environment(Definer* def)
{
	getArgsFromNode(def);
	CORE_Resources::environments[name] = this;
}

void Environment::getArgsFromNode(Definer* def)
{
	name = def->getVariable("name");

	Definer* roomParent = def->getChild("rooms");
	std::vector<Definer*>* roomVector = roomParent->getChildren();

	for (unsigned int i = 0; i < roomVector->size(); i++)
	{
		Definer* cur = (*roomVector)[i];

		if (cur->getName() != "room")
		{
			continue;
		}

		Room* roomToAdd = new Room(cur);

		rooms[roomToAdd->name] = roomToAdd;
	}
}
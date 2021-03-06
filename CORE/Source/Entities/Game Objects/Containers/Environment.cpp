#include "Environment.h"
#include "CORE.h"
#include "CORE_Resources.h"
#include "CORE_Factory.h"


//Get the fuck rid of this and everything else like it. Services in the namespaces should deal
//with this
Environment::Environment(std::string fileName)
{
	XMLNode def = CORE_Resources::getFirstNodeFromFile(fileName);

	//If loading directly from a file, this should be defined in the first node
	if (def.getName() != "environment")
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

Environment::Environment(XMLNode def)
{
	getArgsFromNode(def);
	CORE_Resources::environments[name] = this;
}

void Environment::getArgsFromNode(XMLNode def)
{
	name = def.getVariable("name");

	XMLNode roomParent = def.getChild("rooms");
	std::vector<XMLNode> roomVector = roomParent.getChildren();

	// Get all rooms from "rooms" node
	for (int i = 0; i < roomVector.size(); i++)
	{
		XMLNode cur = roomVector[i];

		Room* roomToAdd = new Room(cur);

		rooms[roomToAdd->name] = roomToAdd;
	}

	// Get all rooms from main node. If a node is not the 
	// name or rooms node, it is assumed to be just a room
	roomVector = def.getChildren({ "rooms", "name" });

	for(int i = 0; i < roomVector.size(); i++)
	{
		XMLNode cur = roomVector[i];

		Room* roomToAdd = new Room(cur);
		rooms[roomToAdd->name] = roomToAdd;
	}
}
#pragma once
#include "Room.h"
#include <map>

/*
	The highest level translation unit for objects that appear in the 'game world.'
	Provides access to and tracks a set of rooms. Environments, in turn, are tracked by
	CORE_Factory. Environments provide the first step in the interface between CORE and
	its game objects. Apart from prototypes and the like, no rooms or objects can exist in
	CORE outside of an environment.
*/

class Environment
{
public:
	std::map<std::string, Room*> rooms;

	Environment(std::string fileName);
	Environment(Node* def);

	std::string name;

private:
	void getArgsFromNode(Node* def);
};
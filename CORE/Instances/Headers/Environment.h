#pragma once
#include "Room.h"
#include <map>
class Environment
{
public:
	std::map<std::string, Room*> rooms;

	Environment(std::string fileName);
	Environment(pugi::xml_node node);

	std::string name;

private:
	void getArgsFromNode(pugi::xml_node node);
};
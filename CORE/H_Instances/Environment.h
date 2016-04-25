#pragma once
#include "Room.h"
#include <map>
class Environment
{
public:
	std::map<std::string, Room*> rooms;

	Environment(char* fileName);

	std::string name;
};
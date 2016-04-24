#pragma once
#include "Room.h"
#include <map>
class Environment
{
public:
	std::map<Room*, std::string> rooms;

	Environment(char* fileName);

	std::string name;
};
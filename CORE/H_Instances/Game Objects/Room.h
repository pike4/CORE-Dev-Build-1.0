#pragma once
#include "Updatable.h"
#include "BaseObject.h"
#include "Visible.h"
#include "Collidable.h"
#include "Pugixml.hpp"
#include <vector>

class Room
{
public:

	std::vector<Updatable*>* updateVector;
	std::vector<Visible*>* drawVector;
	std::vector<BaseObject*>* objectVector;
	std::vector<Collidable*>* collidableVector;

	Room(pugi::xml_node);
};
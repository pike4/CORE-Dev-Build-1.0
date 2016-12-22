#pragma once
#include "BaseObject.h"
#include "Collidable.h"
#include "Room.h"
#include "pugixml.hpp"

class TriggerZone : public BaseObject, public Collidable
{
public:
	TriggerZone(pugi::xml_node node, std::vector<BaseObject*>* objectVector, std::vector<Collidable*>* collidableVector);

};
#include "TriggerZone.h"

TriggerZone::TriggerZone(pugi::xml_node node, std::vector<BaseObject*>* objectVector, std::vector<Collidable*>* collidableVector)
	:BaseObject(node, objectVector), Collidable(node, collidableVector)
{

}
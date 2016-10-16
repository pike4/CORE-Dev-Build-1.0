#include "Mover.h"
#include "GameObject.h"

void Mover::addTo(GameObject* object)
{
	Component::addTo(object);
	object->listeners.push_back(this);
}
#include "Component.h"
#include "GameObject.h"

void Component::addTo(GameObject* object)
{
	if (object != NULL)
	{
		parent = object;

		object->components.push_back(this);
	}
}
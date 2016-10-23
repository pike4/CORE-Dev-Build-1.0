#include "Component.h"
#include "Entity.h"

#include <cstring>

void Component::registerSelf(Entity* newParent)
{
	for (int i = 0; i < events.size(); i++)
	{
		parent->registerListener(events[i], this);
	}
}

Component* Component::spawnCopy()
{
	//TODO: warning this should not have been called, please overload
	printf("warning: spawnCopy should not have been called, please overload\n");
	return NULL;
}

void Component::assignPointers(Entity* parent)
{
	for (int i = 0; i < pointers.size(); i++)
	{
		parent->getPointer(pointers[i]);
	}
}
#include "Component.h"
#include "Entity.h"

void Component::registerSelf(Entity* newParent)
{
	parent = newParent;

	for (int i = 0; i < events.size(); i++)
	{
		parent->registerListener(events[i], this);
	}

	assignPointers(parent);
}

Component* Component::spawnCopy()
{
	//TODO: warning this should not have been called, please overload
	printf("warning: spawnCopy should not have been called, please overload\n");
	return NULL;
}
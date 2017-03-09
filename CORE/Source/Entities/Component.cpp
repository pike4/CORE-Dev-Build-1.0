#include "Component.h"
#include "Entity.h"

#include <cstring>

#pragma region Creational
Component::Component()
{
	ID = std::to_string((rand() << 0) | rand());
}

void Component::storeChild(Component* child)
{
	//warning TODO error: attempted to add child component to basic component. Child will not be added
}

Component* Component::spawnCopy()
{
	printf("warning: spawnCopy should not have been called, please overload\n");
	return NULL;
}

void Component::finalize() {}

//Component gets no data or text by default
void Component::getText(Node* def) {}

void Component::get_data(DataSource* source) {}

#pragma endregion

#pragma region Type Reflection

bool Component::isBasicComponent()
{
	return false;
}
#pragma endregion

#pragma region Parent Registration
void Component::registerEvents(Entity* newParent)
{
	if (!parent)
	{
		printf("NULL parent\n");
		return;
	}

	for (unsigned int i = 0; i < events.size(); i++)
	{
		parent->addListener(events[i], this);
	}
}
#pragma endregion

//void* Component::findAncestorPointer(std::string name) const
//{
//	void* temp = NULL;
//
//	if (parent)
//	{
//		temp = parent->findPointer(name);
//
//		if (!temp)
//		{
//			return parent->findAncestorPointer(name);
//		}
//	}
//
//	return temp;
//}
#include "Entity.h"
#include "Collidable.h"
#include "Controllable.h"
#include "I_DrawComponent.h"

#include "ObjectManager.h"

#include "ComponentTypes.h"

#include <cstring>
#include <iostream>

Entity::Entity()
{
	x = (int*)getPointer("x", 4);
	y = (int*)getPointer("y", 4);
}

Entity::Entity(pugi::xml_node node)
	:Entity()
{
	getArgsFromNode(node);
}

Entity::Entity(Entity& other)
	: Entity()
{
	zIndex = other.zIndex;
	for (int i = 0; i < other.components.size(); i++)
	{
		Component* g = other.components[i]->spawnCopy();
		add(g);
	}
}

void Entity::getArgsFromNode(pugi::xml_node node)
{
	int tempX = atoi(node.child("x").first_child().value());
	int tempY = atoi(node.child("y").first_child().value());
	int tempZ = atoi(node.child("zIndex").first_child().value());
	zIndex = tempZ;

	if (parent)
	{
		parentXOffset = tempX + parent->getAbsoluteX();
		parentYOffset = tempY + parent->getAbsoluteY();
	}

	else
	{
		*x = tempX;
		*y = tempY;
	}

	pugi::xml_node tempNode = node.child("Components");

	tempNode = tempNode.first_child();
	std::string tempName = tempNode.name();

	while (!tempName.empty())
	{
		Component* newComponent = NULL;

		if (newComponent = ObjectManager::generateVisibleElement(tempName, tempNode))
		{
			components.push_back(newComponent);
		}

		else if (newComponent = ObjectManager::generateControl(tempName, tempNode))
		{
			components.push_back(newComponent);
		}

		else if (newComponent = ObjectManager::generateComponent(tempName, tempNode))
		{
			components.push_back(newComponent);
		}

		else if (!tempName.compare("Data"))
		{
			pugi::xml_node dataNode = tempNode.first_child();
			std::string dataName = dataNode.name();

			while (!dataName.empty())
			{
				int size = atoi(dataNode.first_child().value());

				if (size > 0 && size < 100)
				{
					data[dataName] = malloc(size);
				}

				dataNode = dataNode.next_sibling();
				dataName = dataNode.name();
			}
		}

		else
		{
			printf("Undefined object type: %s", tempName.c_str());
		}

		tempNode = tempNode.next_sibling();
		tempName = tempNode.name();
	}

	for (int i = 0; i < components.size(); i++)
	{
		recursiveAdd(components[i]);
	}
}

int Entity::registerListener(int key, Controllable* listener)
{
	if (listeners.find(key) == listeners.end())
	{
		listeners[key] = new std::vector<Controllable*>;
	}

	std::vector<Controllable*>* temp = listeners[key];
	temp->push_back(listener);
	
	return 1;
}

int Entity::deregisterListener(int key, Controllable* listener)
{
	if (listeners.find(key) == listeners.end())
	{
		//Event does not exist
		return 0;
	}

	std::vector<Controllable*>* list = listeners[key];

	for (int i = 0; i < list->size(); i++)
	{
		if (listener == (*list)[i])
		{
			list->erase(list->begin() + i);
			return 1;
		}
	}

	//Element was not found
	return 0;
}

//continuumspooky - finish this
void Entity::add(Component* component)
{
	if (!component)
	{
		printf("NULL COMPONENT\n");
		return;
	}

	components.push_back(component);
	component->parent = this;
	component->assignPointers(this);
	component->registerSelf(this);
}

//Recursively register all components in the vector
void Entity::recursiveAdd(Component* component)
{
	component->parent = this;
	component->assignPointers(this);
	component->registerSelf(this);
}

void Entity::registerSelf(Entity* parent)
{
	Component::registerSelf(parent);

	for (int i = 0; i < components.size(); i++)
	{
		recursiveAdd(components[i]);
	}
}

//Return a pointer 
void* Entity::getPointer(std::string key, int size)
{
	if (data.find(key) == data.end())
	{
		data[key] = calloc(1, size);
	}

	return data[key];
}

void Entity::getPointer(field& pointer)
{
	void* temp = getPointer(pointer.name, pointer.size);
	std::memcpy(pointer.pointer, &temp, pointer.size);
	//std::memcpy((void*)*((int*)pointer.pointer), pointer.pointer, pointer.size);
}

//Sets the given pointer and its associated slot in the data table 
//return the other pointer so it may be assigned to a member pointer
void* Entity::setPointer(std::string key, int size, void* other)
{
	if (data.find(key) == data.end())
	{
		data[key] = calloc(1, size);
	}
	
	data[key] = other;
	return other;
}

//Return the pointer if it exists
void* Entity::findPointer(std::string name) 
{
	void* ret = NULL;

	if (data.find(name) != data.end())
	{
		ret = data[name];
	}

	return ret;
}

void Entity::handleInput(int key, int upDown, int x, int y)
{
	if (listeners.find(key) == listeners.end())
	{
		//TODO
		//warning: key not found
		return;
	}

	std::vector<Controllable*> listenerList = *(listeners[key]);

	for (int i = 0; i < listenerList.size(); i++)
	{
		listenerList[i]->handleInput(key, upDown, x, y);
	}
}

void Entity::move(int aX, int aY)
{
	int* X = (int*)getPointer("x", sizeof(int));
	int* Y = (int*)getPointer("y", sizeof(int));

	*X = aX;
	*Y = aY;
}

int Entity::getAbsoluteX()
{
	return *x + parentXOffset;
}

int Entity::getAbsoluteY()
{
	return *y + parentYOffset;
}
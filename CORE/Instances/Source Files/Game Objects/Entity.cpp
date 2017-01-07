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
	for (unsigned int i = 0; i < other.components.size(); i++)
	{
		Component* newComponent = other.components[i]->spawnCopy();
		components.push_back(newComponent);
	}
}

void Entity::getArgsFromNode(pugi::xml_node node)
{
	int tempZ = atoi(node.child("zIndex").first_child().value());
	zIndex = tempZ;


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

		if (newComponent)
		{
			newComponent->parent = this;
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
					//data[dataName] = malloc(size);
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
}

int Entity::addListener(int key, Controllable* listener)
{
	int ret = 1;

	if (listeners.find(key) == listeners.end())
	{
		ret = 0;
		//Allocate a vector for the given key
		listeners[key] = new std::vector<Controllable*>;

		//Register self with parent for the given key so that the child can receive the event
		if (parent)
		{
			parent->addListener(key, this);
		}
	}

	listeners[key]->push_back(listener);
	
	return ret;
}

int Entity::removeListener(int key, Controllable* listener)
{
	if (listeners.find(key) == listeners.end())
	{
		//Nothing is listening for the event
		return 0;
	}

	std::vector<Controllable*>* list = listeners[key];

	for (unsigned int i = 0; i < list->size(); i++)
	{
		if (listener == (*list)[i])
		{
			list->erase(list->begin() + i);

			/*If there are no more listeners for the given event, remove the entry from
			the map and stop listening for the event*/
			if (list->empty())
			{
				delete list;
				listeners.erase(key);

				if (parent)
				{
					removeListener(key, this);
				}
			}
		}
	}

	//The specified listener was not listening for the event
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

	for (unsigned int i = 0; i < components.size(); i++)
	{
		recursiveAdd(components[i]);
	}
}

//Return a pointer 
//void* Entity::getPointer(std::string key, int size)
//{
//	if (data.find(key) == data.end())
//	{
//		data[key] = calloc(1, size);
//	}
//
//	return data[key];
//}

//Sets the given pointer and its associated slot in the data table 
//return the other pointer so it may be assigned to a member pointer
//void* Entity::setPointer(std::string key, int size, void* other)
//{
//	if (data.find(key) == data.end())
//	{
//		data[key] = calloc(1, size);
//	}
//	
//	data[key] = other;
//	return other;
//}

//Return the pointer if it exists
//void* Entity::findPointer(std::string name) 
//{
//	void* ret = NULL;
//
//	if (data.find(name) != data.end())
//	{
//		ret = data[name];
//	}
//
//	return ret;
//}


Data* Entity::peekData(std::string name)
{
	Data* ret = NULL;

	if (dat.find(name) != dat.end())
	{
		ret = dat[name];
	}

	return ret;
}

void Entity::setData(std::string name, Data* data)
{
	dat[name] = data;
}

void Entity::handleInput(int key, int upDown, int x, int y)
{
	if (listeners.find(key) == listeners.end())
	{
		//warning: key not found
		return;
	}

	std::vector<Controllable*> listenerList = *(listeners[key]);

	for (unsigned int i = 0; i < listenerList.size(); i++)
	{
		Controllable* cur = listenerList[i];
		cur->handleInput(key, upDown, x, y);
	}
}
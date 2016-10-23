#include "Entity.h"
#include "Collidable.h"
#include "Controllable.h"
#include "I_DrawComponent.h"

#include "ObjectManager.h"

#include "ComponentTypes.h"

#include <cstring>

Entity::Entity(pugi::xml_node node)
{
	getArgsFromNode(node);
}

Entity::Entity(Entity& other)
{
	for (int i = 0; i < other.components.size(); i++)
	{
		Component* g = other.components[i]->spawnCopy();
		add(g);
	}
}

void Entity::getArgsFromNode(pugi::xml_node node)
{
	pugi::xml_node tempNode = node.child("Components");

	tempNode = tempNode.first_child();
	std::string tempName = tempNode.name();

	while (!tempName.empty())
	{
		if (!tempName.compare("Animation"))
		{
			add(new Animation(tempNode));
		}

		else if (!tempName.compare("ImageElement"))
		{
			add(new ImageElement(tempNode));
		}

		else if (!tempName.compare("StaticTextElement.h"))
		{
			add(new StaticTextElement(tempNode));
		}

		else if (!tempName.compare("I_VelocityControl"))
		{
			add(new I_VelocityControl(tempNode));
		}

		else if (!tempName.compare("Position"))
		{
			add(new Position(tempNode));
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

		else if (!tempName.compare("Collidable"))
		{
			Collidable* newCollidable = new Collidable(node);
			newCollidable->parent = this;
			components.push_back(newCollidable);
		}

		else
		{
			VisibleElement* temp = ObjectManager::generateVisibleElement(tempName, tempNode);

			if (temp)
			{
				add(temp);
			}
		}

		tempNode = tempNode.next_sibling();
		tempName = tempNode.name();
	}
	int aawdadaw = 0;
}

int Entity::registerListener(int key, Controllable* listener)
{
	if (listeners.find(key) == listeners.end())
	{
		listeners[key] = new std::vector<Controllable*>;
	}

	listeners[key]->push_back(listener);
	
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
	//What have I become

	void* f = pointer.pointer;

	int* g = (int*)f;
	void* h = (void*)g;

	//std::memcpy((void*)*((int*)pointer.pointer), pointer.pointer, pointer.size);
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
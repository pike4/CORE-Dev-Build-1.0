#include "GameObject.h"
#include "BaseObject.h"
#include "Drawable.h"
#include "Updatable.h"
#include "Collidable.h"
#include "Controllable.h"
#include "I_DrawComponent.h"
#include "I_VelocityControl.h"
#include "Position.h"
#include "ObjectManager.h"

GameObject::GameObject(pugi::xml_node node)
{
	getArgsFromNode(node);
}

GameObject::GameObject(GameObject& other)
{
	for (int i = 0; i < other.components.size(); i++)
	{
		components.push_back(other.components[i]->spawnCopy());
		components[i]->registerSelf(this);
	}
}

void GameObject::getArgsFromNode(pugi::xml_node node)
{
	pugi::xml_node tempNode = node.child("Components");

	tempNode = tempNode.first_child();
	std::string tempName = tempNode.name();

	while (!tempName.empty())
	{
		if (!tempName.compare("I_DrawComponent"))
		{
			I_DrawComponent* newDrawComponent = new I_DrawComponent(tempNode);
			newDrawComponent->registerSelf(this);
			components.push_back(newDrawComponent);
		}

		else if (!tempName.compare("I_VelocityControl"))
		{
			I_VelocityControl* newComp = new I_VelocityControl(tempNode);
			newComp->registerSelf(this);
			components.push_back(newComp);
		}

		else if (!tempName.compare("Position"))
		{
			Position* newC = new Position(tempNode);
			newC->registerSelf(this);
			components.push_back(newC);
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

		else if (!tempName.compare("Mobile"))
		{
			//components.push_back(new Mobile(tempNode));
		}

		else if (!tempName.compare("Collidable"))
		{
			Collidable* newCollidable = new Collidable(node);
			newCollidable->parent = this;
			components.push_back(newCollidable);
		}

		tempNode = tempNode.next_sibling();
		tempName = tempNode.name();
	}
	int aawdadaw = 0;
}

int GameObject::registerListener(int key, Controllable* listener)
{
	if (listeners.find(key) == listeners.end())
	{
		listeners[key] = new std::vector<Controllable*>;
	}

	listeners[key]->push_back(listener);
	
	return 1;
}

int GameObject::deregisterListener(int key, Controllable* listener)
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

//Return a pointer 
void* GameObject::getPointer(std::string key, int size)
{
	if (data.find(key) == data.end())
	{
		data[key] = malloc(size);
	}

	return data[key];
}

void GameObject::handleInput(int key, int upDown, int x, int y)
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

void GameObject::move(int x, int y)
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->move(x, y);
	}
}
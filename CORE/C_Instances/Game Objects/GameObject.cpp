#include "GameObject.h"
#include "BaseObject.h"
#include "Drawable.h"
#include "Updatable.h"
#include "Collidable.h"
#include "Controllable.h"
#include "ObjectManager.h"

GameObject::GameObject(pugi::xml_node node)
	: BaseObject(node)
{
	getArgsFromNode(node);
}

GameObject::GameObject(GameObject& other)
	:BaseObject(other)
{
	updatable = other.updatable;
	controllable = other.controllable;

	if (other.motionComponent != NULL)
	{
		motionComponent = other.motionComponent->spawnCopy();
		listeners.push_back(motionComponent);
		motionComponent->parent = this;
	}

	for (int i = 0; i < other.components.size(); i++)
	{
		components.push_back(other.components[i]->spawnCopy());
	}
}

void GameObject::getArgsFromNode(pugi::xml_node node)
{
	pugi::xml_node tempNode = node.child("Components");

	tempNode = tempNode.first_child();
	std::string tempName = tempNode.name();

	while (!tempName.empty())
	{
		if (!tempName.compare("VisibleElement"))
		{
			pugi::xml_node tempVisibleNode = tempNode.first_child();
			std::string tempVisibleName = tempVisibleNode.name();
			VisibleElement* tempElement = NULL;

			while (!tempVisibleName.empty())
			{
				tempElement = ObjectManager::generateVisibleElement
					(tempVisibleName, tempVisibleNode);

				if (tempElement != NULL)
				{
					tempElement->parent = this;
					components.push_back(tempElement);
				}

				tempElement = NULL;
				tempVisibleNode = tempVisibleNode.next_sibling();
				tempVisibleName = tempVisibleNode.name();
			}
		}

		else if (!tempName.compare("Data"))
		{
			pugi::xml_node dataNode = tempNode.first_child();
			std::string dataName = dataNode.name();

			while (!dataName.empty())
			{
				publicData[dataName] = atoi(dataNode.first_child().value());

				dataNode = dataNode.next_sibling();
				dataName = dataNode.name();
			}
		}

		else if (!tempName.compare("Mover"))
		{

			Mover* tempMover = ObjectManager::generateMover
				(tempNode.first_child().name(), tempNode.first_child());

			if (tempMover != NULL)
			{
				tempMover->addTo(this);
			}
		}

		else if (!tempName.compare("Mobile"))
		{
			components.push_back(new Mobile(tempNode));
		}

		else if (!tempName.compare("Updatable"))
		{
			std::string isUpdatableStr = tempNode.first_child().value();

			if (!isUpdatableStr.compare("true"))
			{
				updatable = true;
			}
		}

		else if (!tempName.compare("Collidable"))
		{
			Collidable* newCollidable = new Collidable(node);
			newCollidable->parent = this;
			components.push_back(newCollidable);
		}

		else if (!tempName.compare("Controllable"))
		{
			std::string isControllableStr = tempNode.first_child().value();

			if (!isControllableStr.compare("true"))
			{
				controllable = true;
			}
		}
		tempNode = tempNode.next_sibling();
		tempName = tempNode.name();
	}
	int aawdadaw = 0;
}


void GameObject::handleInput(int key, int upDown, int x, int y)
{
	//TODO
	//warning: this should have been overloaded. Set controllable to false or overload the 
	//handleInput() method in the derived class this was called from

	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i]->handleInput(key, upDown, x, y);
	}

	int a = 0;
}

void GameObject::update()
{
	//TODO
	//warning: this should have been overloaded. Set updatable to false or overload the 
	//update() method in the derived class this was called from
	if(motionComponent != NULL)
	motionComponent->updatePos();
}

void GameObject::move(int x, int y)
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->move(x, y);
	}
}

bool GameObject::isUpdatable()
{
	return updatable;
}

bool GameObject::isControllable()
{
	return controllable;
}
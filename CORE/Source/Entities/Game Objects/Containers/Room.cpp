#include "Room.h"
#include "CORE_Resources.h"
#include "CORE.h"
#include "CORE_Factory.h"
#include "Entity.h"

//Load room from node
Room::Room(Node* definer)
{
	getArgsFromNode(definer);
}

//Load room from file- TODO: DELET file IO is the responsibility of Resources
Room::Room(std::string fileName)
{
	Node* def = CORE_Resources::getFirstNodeFromFile(fileName);

	if (def)
	{
		getArgsFromNode(def);
	}
}

#pragma region adders and removers

void Room::add(Entity* object)
{
		controllableVector->push_back(object);
}

void Room::remove(Controllable* component)
{
	for (unsigned int i = 0; i < controllableVector->size(); i++)
	{
		if ((*controllableVector)[i] == component)
		{
			controllableVector->erase(controllableVector->begin() + i, controllableVector->begin() + i);
			return;
		}
	}

	//TODO:
	//Log warning: component not found
}

#pragma endregion

void Room::spawn(std::string objectName)
{
	if (objectName.empty())
	{
		return;
	}

	Entity* newObject = CORE_Factory::generate(objectName);

	add(newObject);
}

void Room::getArgsFromNode(Node* def)
{
	controllableVector = new std::vector<Controllable*>;

	Node* controlsParent = def->getChild("objects");
	if (controlsParent)
	{
		std::vector<Node*>* objectsVector = controlsParent->getChildren();

		for (unsigned int i = 0; i < objectsVector->size(); i++)
		{
			Node* cur = (*objectsVector)[i];

			Entity* newObject = (Entity*) CORE_Factory::generateObject(cur);
			add(newObject);
		}
	}

	name = def->getVariable("name");
	w = stoi(def->getVariable("w"));
	h = stoi(def->getVariable("h"));
}

void Room::handleInput(int key, int posOrNeg, int x, int y)
{
	for (unsigned int i = 0; i < controllableVector->size(); i++)
	{
		if ((*controllableVector)[i] != NULL)
		{
			(*controllableVector)[i]->handleInput(key, posOrNeg, x, y);
		}
	}
}

void Room::draw()
{
	for (unsigned int i = 0; i < controllableVector->size(); i++)
	{
		if ((*controllableVector)[i] != NULL)
		{
			(*controllableVector)[i]->handleInput(drawStep);
		}
	}
}

void Room::update()
{
	for (unsigned int i = 0; i < controllableVector->size(); i++)
	{
		if ((*controllableVector)[i] != NULL)
		{
			(*controllableVector)[i]->handleInput(updateStep);
		}

		else
		{
			printf("NULL update in room\n");
		}
	}
}
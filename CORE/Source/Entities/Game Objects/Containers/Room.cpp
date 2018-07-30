#include "Room.h"
#include "CORE_Resources.h"
#include "CORE.h"
#include "CORE_Factory.h"
#include "Entity.h"
#include "Events.h"

//Load room from node
Room::Room(XMLNode definer)
{
	getArgsFromNode(definer);
}

//Load room from file- TODO: delete. file IO is the responsibility of Resources
Room::Room(std::string fileName)
{
	XMLNode def = CORE_Resources::getFirstNodeFromFile(fileName);

	if (!def.null())
	{
		getArgsFromNode(def);
	}
}

#pragma region adders and removers

void Room::add(Entity* object)
{
	entityQueue.push_back(object);
}

void Room::insertEntity(Entity* newEntity)
{
	controllableVector->push_back(newEntity);

	Event newEntityEvent = entity_added;
	newEntityEvent.arguments.push_back(newEntity);

	handle(newEntityEvent);
}

void Room::remove(Controllable* component)
{
	for (int i = 0; i < controllableVector->size(); i++)
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

void Room::getArgsFromNode(XMLNode def)
{
	controllableVector = new std::vector<Controllable*>;

	XMLNode objectsParent = def.getChild("objects");
	if (!objectsParent.null())
	{
		std::vector<XMLNode> objectsVector = objectsParent.getChildren();

		for (int i = 0; i < objectsVector.size(); i++)
		{
			XMLNode cur = objectsVector[i];

			Entity* newObject = (Entity*) CORE_Factory::generateObject(cur);

			if (newObject)
			{
				newObject->finalize();
				newObject->registerEv(this);
			}

			add(newObject);
		}
	}

	name = def.getName();
	w = Util::toInt(def.getVariable("w"));
	h = Util::toInt(def.getVariable("h"));

	std::vector<XMLNode> otherChildren = def.getChildren( { "objects", "w", "h" } );

	for(int i = 0; i < otherChildren.size(); i++)
	{
		XMLNode cur = otherChildren[i];

		Entity* newObject = (Entity*)CORE_Factory::generateObject(cur);

		if (newObject)
		{
			newObject->finalize();
			newObject->registerEv(this);
		}

		add(newObject);
	}
}

void Room::handle(Event e)
{
	if (observers.find(e.opcode) != observers.end())
	{
		std::vector<Controllable*> vec = observers[e.opcode];
		for (int i = 0; i < vec.size(); i++)
		{
			vec[i]->handle(e);
			vec[i]->update();
		}
	}
}

void Room::receive(Event e)
{
	if (observers.find(e.opcode) != observers.end())
	{
		std::vector<Controllable*> vec = observers[e.opcode];
		for (int i = 0; i < vec.size(); i++)
		{
			vec[i]->receive(e);
		}
	}
}

void Room::direct(Event e, Entity* ancestor)
{
	if (observers.find(e.opcode) != observers.end())
	{
		std::vector<Controllable*> vec = observers[e.opcode];
		for (int i = 0; i < vec.size(); i++)
		{
			vec[i]->condReceive(e, ancestor);
		}
	}
}

void Room::draw()
{
	handle(drawStep);
}

void Room::update()
{
	emptyQueue();

	handle(updateStep);
}



void Room::emptyQueue()
{
	while(!entityQueue.empty())
	{
		insertEntity(entityQueue[ entityQueue.size() - 1 ]);
		entityQueue.pop_back();
	}
}
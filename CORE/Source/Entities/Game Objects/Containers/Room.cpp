#include "Room.h"
#include "CORE_Resources.h"
#include "CORE.h"
#include "CORE_Factory.h"
#include "Entity.h"

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

void Room::getArgsFromNode(XMLNode def)
{
	controllableVector = new std::vector<Controllable*>;

	XMLNode controlsParent = def.getChild("objects");
	if (!controlsParent.null())
	{
		std::vector<XMLNode> objectsVector = controlsParent.getChildren();

		for (unsigned int i = 0; i < objectsVector.size(); i++)
		{
			XMLNode cur = objectsVector[i];

			Entity* newObject = (Entity*) CORE_Factory::generateObject(cur);

			if (newObject)
			{
				newObject->finalize();
				newObject->registerRoom(this);
			}

			add(newObject);
		}
	}

	name = def.getName();
	w = stoi(def.getVariable("w"));
	h = stoi(def.getVariable("h"));
}

void Room::handle(Event e)
{
	for (unsigned int i = 0; i < controllableVector->size(); i++)
	{
		if ((*controllableVector)[i] != NULL)
		{
			(*controllableVector)[i]->handle(e);
		}
	}

	if (observers.find(e.opcode) != observers.end())
	{
		std::vector<Controllable*> vec = observers[e.opcode];
		for (int i = 0; i < vec.size(); i++)
		{
			vec[i]->handle(e);
		}
	}
}

void Room::draw()
{
	for (unsigned int i = 0; i < controllableVector->size(); i++)
	{
		if ((*controllableVector)[i] != NULL)
		{
			(*controllableVector)[i]->handle(drawStep);
		}
	}
}

void Room::update()
{
   emptyQueue();

	for (unsigned int i = 0; i < controllableVector->size(); i++)
	{
		if ((*controllableVector)[i] != NULL)
		{
			(*controllableVector)[i]->handle(updateStep);
		}

		else
		{
			printf("NULL update in room\n");
		}
	}
}

void Room::emptyQueue()
{
   while(!entityQueue.empty())
   {
      insertEntity(entityQueue[ entityQueue.size() - 1 ]);
      entityQueue.pop_back();
   }
}

void Room::registerEvent(int opcode, Controllable* observer)
{
	if (observers.find(opcode) == observers.end())
	{
		observers[opcode] = std::vector<Controllable*>();
	}

	observers[opcode].push_back(observer);
}

void Room::unregisterEvent(int opcode, Controllable* observer)
{
	if (observers.find(opcode) != observers.end()) 
	{
		for (int i = 0; i < observers[opcode].size(); i++)
		{
			if (observers[opcode][i] == observer) {
				observers[opcode].erase(observers[opcode].begin() + i);
			}
		}
	}
}

void Room::unregisterObserver(Controllable* observer)
{
	for (std::map<int, std::vector<Controllable*>>::iterator it = observers.begin(); it != observers.end(); ++it)
	{
		unregisterEvent(it->first, observer);
	}
}
#include "Entity.h"
#include "Collidable.h"
#include "Controllable.h"
#include "CORE.h"
#include "CORE_Resources.h"
#include "CORE_Factory.h"
#include "ComponentTypes.h"

#include <cstring>
#include <iostream>

Entity::Entity()
{
	ID = CORE::storeObject(this);
	DataImpl<int>* myID = new DataImpl<int>();
	*myID = ID;

	data["ID"] = myID;
}

Entity::Entity(Entity& other)
	: Entity()
{
	for (int i = 0; i < other.components.size(); i++)
	{
		Component* newComponent = other.components[i]->spawnCopy();
		components.push_back(newComponent);
	}
}

Entity* Entity::getContext()
{
	return this;
}

/**
	Retrieve all data pointers from the DataSource and copy to this Entity's data map
*/
void Entity::get_data(DataSource* source)
{
	std::vector<std::pair<std::string, reflection>> srcData = source->getAllData();

	for (int i = 0; i < srcData.size(); i++)
	{
		data[srcData[i].first] = srcData[i].second.pointer;
	}
}

void Entity::getArgsFromNode(XMLNode definer)
{}

int Entity::addListener(int key, Controllable* listener)
{
	int ret = 1;

	if (listeners.find(key) == listeners.end())
	{
		ret = 0;
		//Allocate a vector for the given key
		listeners[key] = std::vector<Controllable*>();

		//Register self with parent for the given key so that the child can 
		//receive the event
		if (parent)
		{
			parent->addListener(key, this);
		}
	}

	// Add the listener to the list for the given event
	listeners[key].push_back(listener);
	
	return ret;
}

int Entity::removeListener(int key, Controllable* listener)
{
	if (listeners.find(key) == listeners.end())
	{
		//Nothing is listening for the event
		return 0;
	}

	std::vector<Controllable*> list = listeners[key];

	for (int i = 0; i < list.size(); i++)
	{
		if (listener == list[i])
		{
			list.erase(list.begin() + i);

			/*If there are no more listeners for the given event, remove the entry from
			the map and stop listening for the event*/
			if (list.empty())
			{
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

void Entity::storeChild(Component* component)
{
	if (!component)
	{
		printf("NULL COMPONENT\n");
		return;
	}

	components.push_back(component);
	component->parent = this;
}

/**
	Perform depth-first traversal of child components, assigning parent pointers 
	and registering for events
*/
void Entity::finalize()
{
	for (int i = 0; i < components.size(); i++)
	{
		Component* component = components[i];

		component->parent = this;
		component->finalize();
	}
}

void Entity::registerEv(MessagePasser* passer)
{
	Component::registerEv(passer);

	for (int i = 0; i < components.size(); i++)
	{
		components[i]->registerEv(passer);
	}
}

Data* Entity::getRawPtr(std::string name)
{
	 if (data.find(name) != data.end())
	 {
		  return data[name];
	 }

	 return NULL;
}

void Entity::setData(std::string name, Data* newData)
{
	data[name] = newData;
}

//
bool Entity::getTrait(std::string trait)
{
	bool ret = false;

	DataImpl<bool>* t = peekData<bool>(trait);

	if (t)
	{
		ret = *t;
	}

	return ret;
}

void Entity::on(std::string eventName, std::string handlerName)
{
	EventHandler* handler = CORE_Resources::getEventHandler(handlerName);


	if (!handler)
		CORE_SystemIO::error("Event Handler " + handlerName + " does not exist");

	else if (CORE_Resources::events.find(eventName) == CORE_Resources::events.end())
		CORE_SystemIO::error("Event " + eventName + " does not exist");

	else if (CORE_Resources::events[eventName].format
		!= CORE_Resources::eventHandlers[handlerName]->format)
		CORE_SystemIO::error("Event handler " + handlerName + " does not exist");

	else
		eventHandlers[CORE_Resources::getEventCode(eventName)].push_back(handler);
}

void Entity::handle(Event e) {}

int Entity::getID()
{
	return ID;
}

/**
 *  Get a vector of key-value pairs representing all data members in the entity
 */
std::vector<std::pair<std::string, Data*>> Entity::getAllData()
{
	std::vector<std::pair<std::string, Data*>>  ret;
	std::map<std::string, Data*>::iterator iter;
	for (iter = data.begin(); iter != data.end(); ++iter)
	{
		ret.push_back(std::pair<std::string, Data*>(iter->first, iter->second));
	}

	return ret;
}
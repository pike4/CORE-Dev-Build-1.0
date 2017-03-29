#include "Entity.h"
#include "Collidable.h"
#include "Controllable.h"

#include "CORE_Resources.h"
#include "CORE_Factory.h"
#include "ComponentTypes.h"

#include <cstring>
#include <iostream>

Entity::Entity()
{
}

Entity::Entity(Entity& other)
	: Entity()
{
	for (unsigned int i = 0; i < other.components.size(); i++)
	{
		Component* newComponent = other.components[i]->spawnCopy();
		components.push_back(newComponent);
	}
}

void Entity::get_data(DataSource* source)
{
	//Copy each data into the data map
	//DataSource needs [] operator or getChildren method
	//for (std::map<std::string, reflection>::iterator it = dataMap->begin(); it != dataMap->end(); ++it)
	//{
	//	data[it->first] = it->second.pointer;
	//}
}

void Entity::getArgsFromNode(Node* definer)
{
	//Node* componentsNode = definer->getChild("components");

	//if (componentsNode)
	//{
	//	std::vector<Node*>* componentsNodes = componentsNode->getChildren();

	//	if (componentsNodes)
	//	{
	//		for (unsigned int i = 0; i < componentsNodes->size(); i++)
	//		{
	//			Node* curDefiner = (*componentsNodes)[i];
	//			Component* newComponent = NULL;

	//			if (newComponent = CORE_Factory::constructVisibleElement(curDefiner))
	//			{
	//				components.push_back(newComponent);
	//			}

	//			else if (newComponent = CORE_Factory::constructControl(curDefiner))
	//			{
	//				components.push_back(newComponent);
	//			}

	//			else if (newComponent = CORE_Factory::generateComponent(curDefiner))
	//			{
	//				components.push_back(newComponent);
	//			}

	//			if (newComponent)
	//			{
	//				newComponent->parent = this;
	//			}

	//			else
	//			{
	//				printf("Undefined object type %s\n", curDefiner->getName().c_str());
	//			}
	//		}
	//	}
	//}
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

//Perform a depth first traversal assigning parent pointers and registering for events
void Entity::finalize()
{
	for (int i = 0; i < components.size(); i++)
	{
		Component* component = components[i];

		component->parent = this;
		component->finalize();
	}

	for (int i = 0; i < components.size(); i++)
	{
		components[i]->registerEvents(this);
	}
}

void Entity::registerEvents(Entity* parent)
{
	if (parent)
	{
		Component::registerEvents(parent);
	}
}

Data* Entity::peekData(std::string name)
{
	Data* ret = NULL;

	if (data.find(name) != data.end())
	{
		ret = data[name];
	}

	return ret;
}

void Entity::setData(std::string name, Data* newData)
{
	data[name] = newData;
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

void Entity::on(std::string eventName, std::string handlerName)
{
   if (CORE_Resources::eventHandlers.find(handlerName) != CORE_Resources::eventHandlers.end())
      CORE_SystemIO::error("Event Handler " + handlerName + " does not exist");

   else if (CORE_Resources::events.find(eventName) != CORE_Resources::events.end())
      CORE_SystemIO::error("Event " + eventName + " does not exist");

   else if (CORE_Resources::events[eventName].format
      != CORE_Resources::eventHandlers[handlerName]->format)
      CORE_SystemIO::error("Event handler " + handlerName + " does not exist");

   else
      eventHandlers[eventName].push_back(CORE_Resources::eventHandlers[handlerName]);
}

void Entity::handle(std::string eventName, std::vector<Data*> arguments)
{
   if(eventHandlers.find(eventName) != eventHandlers.end()) 
   {
      std::vector<EventHandler*> handlerVector = eventHandlers[eventName];

      for each(EventHandler* cur in handlerVector)
      {
         cur->handleEvent(arguments);
      }
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
#pragma once
#include "Controllable.h"
#include "Data.h"
#include "Node.h"
#include "DataSource.h"
#include "EventHandler.h"
#include "Event.h"

#include <type_traits>
#include <map>
#include <stdlib.h>
#include <vector>

class MessagePasser;
class Entity;

typedef struct _field
{
	std::string name;
	void* pointer;
}field;

/*
	Component class

	Purpose:
		1. Act as the default translation unit for Entity composition 
			and 
		2. Receive and act on events from the parent Entity
		3. Provide reflection info for what type of object the given component
			represents
*/

class Component : public Controllable
{
public:
	#pragma region Creational
	Component();
	//Get private data from the given XMLNode
	virtual void getText(XMLNode def);

	//Get public Data objects from the given map
	virtual void get_data(DataSource* source);

	//Get event handlers from the given XMLNode
	virtual void getEventHandlers(XMLNode def);

	//Store the child without registering it. Basic components can't have children
	virtual void storeChild(Component* child);

	//Finalize the component. Represents the recursive root for finalizing an Entity
	virtual void finalize();

	//Handle an event
	virtual void handle(Event e);

	//Return true if this component has a certain trait
	virtual bool getTrait(std::string trait);

	template <typename T>
	DataImpl<T>initializeData(std::string name, DataSource* source)
	{
		DataImpl<T> ret = source->getData<T>(name);

		if (parent )
		{
			ret = parent->getData<T>(name);
		}

		return ret;
	}

	virtual Component* spawnCopy();
	#pragma endregion

	//Needed so parent objects don't just add random shit they can't use like adding a CheckBoxButton
	//to a player, or a BossMonster to a GUI_Area
	#pragma region Sub-Type Reflection
	//Determine if this instance can have children
	virtual bool isBasicComponent();

	//Return a pointer to the entity context for the component, in most cases, this is the parent entity
	virtual Entity* getContext();
	
	//TODO: something like get heirarchy, and every component would have a static string name and return
	//its inheiritance heirarchy
	//virtual std::vector<std::string> getHeirarchy();

	//TODO: something like getCategory, where components would have categories like visibleElement, 
	//Control etc
	#pragma endregion

	#pragma region Parent Registration
	virtual void registerEv(MessagePasser* passer);
	#pragma endregion

	std::vector<int> events;
	std::vector<field> pointers;

	Entity* parent;

protected:
	//Maps event names to event handlers that will be called when an event is received
	std::map<int, std::vector< EventHandler*> > eventHandlers;
};
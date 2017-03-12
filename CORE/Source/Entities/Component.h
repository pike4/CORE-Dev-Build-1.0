#pragma once
#include "Controllable.h"
#include "Data.h"
#include "Node.h"
#include "DataSource.h"

#include <type_traits>
#include <map>
#include <stdlib.h>
#include <vector>

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
	//Get private data from the given definer
	virtual void getText(Node* def);

	//Get public Data objects from the given map
	virtual void get_data(DataSource* source);

	//Store the child without registering it. Basic components can't have children
	virtual void storeChild(Component* child);

	//Finalize the component. Represents the recursive root for finalizing an Entity
	virtual void finalize();

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
   
	//TODO: something like get heirarchy, and every component would have a static string name and return
	//its inheiritance heirarchy
   virtual std::vector<std::string> getHeirarchy();
	//TODO: something like getCategory, where components would have categories like visibleElement, 
	//Control etc
	#pragma endregion

	#pragma region Parent Registration
	virtual void registerEvents(Entity* newParent);
	#pragma endregion

	std::vector<int> events;
	std::vector<field> pointers;

	Entity* parent;

protected:
	//ID to *almost certainly* uniquely identify every componenet and entity in order to 
	//prevent hash collisions between parent and child variables of the same name.
	std::string ID;

//private:
	//If we do type reflection for component subtypes when generating, this is probably the way to do it
	//static std::string type;
};
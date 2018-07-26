#pragma once

#include "Node.h"
#include "Component.h"
#include "Controllable.h"
#include "Data.h"
#include "EventHandler.h"

#include "pugixml.hpp"
#include <type_traits>
#include <map>
#include <vector>
#include <set>

/*
	Entity Class
   Represents the lowest-level translation unit that can exist in a room in CORE.
   An entity is
	any instantiable object that can interact with the game world.

   Purpose:
      1. Provide a centralized storage and access location for components belonging 
         to the same object
      2. Receive and process events and forward them to interested child components
      3. Allow data sharing between child components by providing an access point 
         to a common state

   Sub-Components:
      1. Public state storage and access
      2. Event handling and transmission
      3. Instantiation from other entities and XML Nodes
*/
class Entity : public Component
{
public:
	Entity();
	Entity(Entity& other);

   virtual Entity* getContext();
	
#pragma region Instantiation
   virtual void get_data(DataSource* source);
	virtual void storeChild(Component* component);
	void finalize();
#pragma endregion

#pragma region Accessors

	//Return a pointer to the data of the specified type of the given name
	//Allocate a new Data of the specified type if it does not exist
	template <typename T>
	Data* getCompoundData(std::string name)
	{
		Data* ret = NULL;

		if (std::is_base_of<Data, T>())
		{
			if (data.find(name) == data.end())
			{
				T* newData = new T;
				data[name] = (Data*)newData;
			}

			ret = data[name];
		}

		else
		{
			printf("Unsupported data type for compound data");
		}

		return ret;
	}

	/**
      Return a pointer to the data of the given name.
      Allocate a new SimpleData if not present
   */
	template <typename T>
	DataImpl<T>* getData(std::string name)
	{
		DataImpl<T>* ret = NULL;
		
		if (data.find(name) == data.end())
		{
			data[name] = new DataImpl<T>;
		}

      if (dataIsType<T>(data[name]))
      {
         ret = (DataImpl<T>*) data[name];
      }
      
      return ret;
	}

   //Return the value of the data of the given name
   template <typename T>
   T getValue(std::string name)
   {
      T ret = 0;

      DataImpl<T>* data = getData<T>(name);

      if (data)
      {
         ret = *data;
      }

      return ret;
   }

   /**
   Get a data member of the given name, returning NULL if it does not exist
   */
   template <typename T>
   DataImpl<T>* peekData(std::string name)
   {
      DataImpl<T>* ret = NULL;

      if (data.find(name) != data.end())
      {
         if (dataIsType<T>(data[name]))
         {
            ret = (DataImpl<T>*) data[name];
         }

         else
         {
            CORE_SystemIO::error("Data is different type");
         }
      }

      return ret;
   }

   //Get a vector of all Data pointers contained by this Entity
   std::vector<std::pair<std::string, Data*>>  getAllData();

   Data* getRawPtr(std::string name);

	//Set the data of the given name to the given value
	template <typename T>
	void setValue(std::string name, T newValue)
	{
		DataImpl<T>* tempData = (DataImpl<T>*) getData<T>(name);
		*tempData = newValue;
	}

	//Register the data pointer under the given name in the data map
	//This could lead to a dangling pointer if the data already exists! think of a solution.
	//Maybe return the old pointer if it exists, null if it doesn't
	void setData(std::string name, Data* data);

   bool getTrait(std::string trait);

#pragma endregion

#pragma region Message Handling
   void on(std::string eventName, std::string handlerName);

   void handle(Event e);

	//Push recursive add down to children
	virtual void registerEvents(Entity* parent);

	//Listeners
	int addListener(int key, Controllable* listener);
	int removeListener(int key, Controllable* listener);
#pragma endregion

protected:
	//Maps event codes to vectors of Controllable objects that listen for those events
	std::map<int, std::vector<Controllable*>> listeners;

	//Maps string variable names to Data pointers accissible from the 
    //public class interface
	std::map<std::string, Data*> data;

	//The components that make up this object
	std::vector<Component*> components;

	void getArgsFromNode(XMLNode definer);
};
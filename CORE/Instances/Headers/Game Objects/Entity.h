#pragma once

#include "Definer.h"
#include "Component.h"
#include "Controllable.h"
#include "Data.h"

#include "pugixml.hpp"
#include <type_traits>
#include <map>
#include <vector>

class Room;

/*
	Represents the lowest-level translation unit that can exist in a room in CORE. An entity is
	any instantiable object that can interact with the game world.
*/

class Entity : public Component
{
public:
	Entity(Definer* definer);
	Entity(Entity& other);
	Entity();
	
#pragma region Composition
	void add(Component* component);
	void recursiveAdd(Component* component);
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
			if (dat.find(name) == dat.end())
			{
				T* newData = new T;
				dat[name] = (Data*)newData;
			}

			ret = dat[name];
		}

		else
		{
			printf("Unsupported data type for compound data");
		}

		return ret;
	}

	//Return a pointer to the data of the given name. Allocate a new SimpleData if not present
	template <typename T>
	SimpleData<T>* getData(std::string name)
	{
		SimpleData<T>* ret = NULL;

		if (dat.find(name) == dat.end())
		{
			dat[name] = new SimpleData<T>;
		}

		return (SimpleData<T>*) dat[name];
	}

	//Return a pointer to the data of the given name. Return null if not present
	Data* peekData(std::string name);

	//Set the data of the given name to the given value
	template <typename T>
	void setValue(std::string name, T newValue)
	{
		DataImpl<T>* tempData = (DataImpl<T>*) getData<T>(name);
		*tempData = newValue;
	}

	//Register the data pointer under the given name in the data map
	//This could lead to a dangling pointer if the data already exists! think of a solution.
	//MAybe return the old pointer if it exists, null if it doesn't
	void setData(std::string name, Data* data);

	//Return the value of the data of the given name
	template <typename T>
	T getValue(std::string name)
	{
		return get(name);
	}

#pragma endregion

#pragma region Message Handling
	virtual void handleInput(int key, int upDown = 0, int x = 0, int y = 0);

	//Push recursive add down to children
	virtual void registerSelf(Entity* parent);

	//Listeners
	int addListener(int key, Controllable* listener);
	int removeListener(int key, Controllable* listener);
#pragma endregion

protected:

	//Maps event codes to vectors of Controllable objects that listen for those events
	std::map<int, std::vector<Controllable*>*> listeners;

	//Maps string variable names to Data pointers accissible from the public class interface
	std::map<std::string, Data*> dat;

	//The components that make up this object
	std::vector<Component*> components;

	void getArgsFromNode(Definer* definer);
};
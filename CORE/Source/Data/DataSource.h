#pragma once
#include "CORE_TypeTraits.h"
#include "Data.h"
#include "Node.h"

#include <string>
#include <map>

typedef std::map<std::string, CORE_TypeTraits::reflection> TypeTraitMap;

class DataSource
{
public:
   DataSource(Node* ownNode, DataSource* newParent);

	//Return a fully formed and linked Data object to the requestor
	template<typename T>
	DataImpl<T>* getData(std::string name)
	{
		DataImpl<T>* ret = NULL;

		//Return the pointer in the source's map by default
		if (dataMap.find(name) != dataMap.end())
		{
			reflection trait = dataMap[name];

			if (CORE_TypeTraits::dataIsType<T>(&trait))
			{
				ret = (DataImpl<T>*) trait.pointer;
			}

			else
			{
				//TODO warning: requested data is of incompatible type
			}
		}

		//Default to parent data if not in dataMap
		else if (parent)
		{
			reflection* parentTrait = parent->getTrait(name);

			//Verify requested data and parent data are same type
			if (parentTrait)
			{
				if (CORE_TypeTraits::dataIsType<T>(parentTrait))
				{
					ret = (DataImpl<T>*) parentTrait->pointer;
				}

				else
				{
					//Pedantic warning: child data is of differing type from parent
				}
			}
		}

		//Allocate a new Data object as a last resort
		if(!ret)
		{
			//TODO warning: requested data not given in XML file
			ret = new DataImpl<T>(TR_SIMPLE);
		}

		return ret;
	}

   //Return a vector of name-Data pairs representing all of this Source's data
   std::vector<std::pair<std::string, reflection>> getAllData();

	//Return the string of the given name to the requestor from the definer
	std::string getText(std::string name);

private:
	//Node defining
	Node* node;

	//Map of type information for data belonging to requestor
	TypeTraitMap dataMap;	
	
	//Map of type information for data belonging to requestor's parent object
	DataSource* parent;

	//Return a reflection object of the given name
	CORE_TypeTraits::reflection* DataSource::getTrait(std::string name);
};
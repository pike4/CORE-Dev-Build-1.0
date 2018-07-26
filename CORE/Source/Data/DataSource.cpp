#include "DataSource.h"
#include "Node.h"

#include <vector>
using namespace CORE_TypeTraits;

//Reads trait info from XMLNode, binds dependencies between own data and parent data
DataSource::DataSource(XMLNode* def, DataSource* newParent)
{
	if (!(def || newParent))
	{
		//TODO error: cannot initialize data source with NULL sources
		return;
	}

	node = def;
	parent = newParent;
	if ( def )
	{
		std::vector<XMLNode> dataNodes = def->getChildren();

		for (unsigned int i = 0; i < dataNodes.size(); i++)
		{
			XMLNode curNode = dataNodes[i];

			CORE_TypeTraits::reflection curTraits;
			CORE_TypeTraits::parseReflectionTraits(curNode, &curTraits);
			curTraits.pointer = CORE_TypeTraits::generateDataFromReflection(curTraits);

			//Check if a Datum of the given name has already been instantiated for this DataSource
			if (dataMap.find(curTraits.name) != dataMap.end())
			{
				curTraits.good = false;

				bool add = true;
				CORE_TypeTraits::reflection oldTraits = dataMap[curTraits.name];

				if (oldTraits.primitiveType != curTraits.primitiveType)
				{
					//TODO: error: multiple instantiations of variable <name> with conflicting
					//primitive types
					add = false;
				}

				if (oldTraits.funcType != curTraits.funcType)
				{
                CORE_SystemIO::error("multiple instantiations of variable <name> with conflicting function types");
					add = false;
				}

				if (add && (oldTraits.value != curTraits.value))
				{
					CORE_SystemIO::error("warning: multiple instantiations of variable " + curTraits.name + 
                   " with conflicting values. New value will override old value.");
					dataMap[curTraits.name].value = curTraits.value;
				}
			}

			//Assign dependencies between the current Data and the parent's instance if needed
			if (parent)
			{
				//Check if parent has trait of same name
				CORE_TypeTraits::reflection* parentTraits = parent->getTrait(curTraits.name);
				if (parentTraits)
				{
					CORE_TypeTraits::bindDependencies(&curTraits, parentTraits);
				}
			}

			if (curTraits.good)
			{
				dataMap[curTraits.name] = curTraits;
			}

			//Kill the Data pointer and NULL it if it is invalid, for it is better to enter the
			//gameObject with a NULL pointer than to have a valid one and be cast into a corrupted 
			//stack frame, where the exception is not caught, and memory will never be freed.
			else
			{
				//delete curTraits.pointer;
			}
		}
	}
}

std::vector<std::pair<std::string, reflection>> DataSource::getAllData()
{
   std::vector<std::pair<std::string, reflection>> ret;

   for (std::map<std::string, CORE_TypeTraits::reflection>::iterator it = dataMap.begin();
      it != dataMap.end(); ++it)
   {
      std::pair<std::string, reflection> newData = std::pair<std::string, 
         reflection>(it->first, it->second);

      ret.push_back(newData);
   }

   return ret;
}

std::string DataSource::getText(std::string name)
{
	std::string ret = "";

	if ( !node->null() ) 
	{
		 ret = node->getVariable(name);
	}

	return ret;
}

CORE_TypeTraits::reflection* DataSource::getTrait(std::string name)
{
	CORE_TypeTraits::reflection* ret = NULL;

	if (dataMap.find(name) != dataMap.end())
	{
		ret = &dataMap[name];
	}

	return ret;
}

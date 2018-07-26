#pragma once
#include <string>
#include "Node.h"

class Data;
class XMLNode;

/* 
   Type traits subsystem

   Exposes a public API in order to:
      1. Get various type info from a given Data object via a simple function call
      2. Allow verification of the underlying primitive type of Data objects
      3. Parse type traits from XML nodes and generate more descriptive data structures for them
      4. Generate Data objects from their defining type traits
      5. Perform various operations on Data objects such as binding dependencies
*/

//Methods for obtaining and creating type traits for Data objects
namespace CORE_TypeTraits
{
    //Enumerates the various transform types available to Data objects
    enum FuncType : int
    {
        TR_SIMPLE,
        TR_OFFSET,
        TR_SUM,
        TR_AVERAGE
    };

    enum PrimitiveType
    {
        _integer,
        _boolean,
        _string,
        _floatingPoint,
        _entity,
        _state,
        _errorType
    };

    //Whether the datum depends on its parent, children, or nothing
    enum DependenceType
    {
        DP_NONE = 0,
        DP_PARENT,
        DP_CHILDREN,
    };

    //Provides type and linking information for a single Data object
    struct reflection
    {
        //Underlying primitive type for the associated Data object
        PrimitiveType primitiveType;

        //Determines dependency with parent, children, or no dependency
        DependenceType dependenceType;

        //Determines the transform type for the associated Data object
        FuncType funcType;

        //Raw string value
        std::string value;
        std::string name;

        //Dirty state used to prevent invalid data objects from being added
        bool good;

        reflection* parent;		//Pointer to data of same name in parent object
        class Data* pointer;	//The actual Data object this defines
    };

#pragma region Data Object reflection
    template <typename T>
    bool dataIsType(reflection* toCheck)
    {
        bool ret = false;
        if (toCheck)
        {
            switch (toCheck->primitiveType)
            {
            case _integer:
                ret = std::is_same<int, T>();
                break;
            case _floatingPoint:
                ret = std::is_same<double, T>();
                break;
            case _boolean:
                ret = std::is_same<bool, T>();
                break;
            default:
                //TODO error: type provided is undefined or not currently supported
                break;
            }
        }

        return ret;
    }

    template <typename T>
    bool dataIsType(Data* toCheck)
    {
        return (toCheck && toCheck->getType() == typeOfT<T>());
    }

    template <typename T>
    PrimitiveType typeOfT()
    {
        PrimitiveType ret = _errorType;
        if (std::is_same<int, T>())
            ret = _integer;
        else if (std::is_same<bool, T>())
            ret = _boolean;
        else if (std::is_same<double, T>())
            ret = _floatingPoint;

        return ret;
    }

    template <typename T>
    size_t sizeOfT()
    {
        PrimitiveType type = typeOfT<T>();
        return getDataObjectSize(type);
    }
	#pragma endregion

	#pragma region Get traits by name
	PrimitiveType getPrimitiveType(std::string type);
	DependenceType getDependenceType(std::string type);
	FuncType getFunctionType(std::string type);
	#pragma endregion

	#pragma region Get trait names
	std::string getPrimitiveTypeName(PrimitiveType type);
	std::string getTransformTypeName(FuncType type);
	std::string getDependenceTypeName(DependenceType type);
	#pragma endregion

#pragma region Get Data object sizes
   template <typename T>
   size_t getDataObjectSize()
   {
       return sizeof(DataImpl<T>);
   }

   size_t getDataObjectSize(std::string primitiveType);
   size_t getDataObjectSize(PrimitiveType primitiveType);
#pragma endregion

	//Verify validity of and bind dependencies between two Data objects
	void bindDependencies(reflection* child, reflection* parent);

	//Parse out the type traits of a Data object from a XMLNode
	void parseReflectionTraits(XMLNode def, reflection* ret);

	//Generate a new Data object from given type traits
	Data* generateDataFromReflection(reflection datum);
}
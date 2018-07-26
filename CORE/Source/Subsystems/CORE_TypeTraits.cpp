#include "Core_TypeTraits.h"
#include "Data.h"
#include "Node.h"
#include "DataSource.h"

#include <type_traits>

namespace CORE_TypeTraits
{

	Data* generateDataFromReflection(reflection datum)
	{
		Data* ret = NULL;

		switch (datum.primitiveType)
		{
		case _integer:
			ret = new DataImpl<int>(datum.funcType);
			(*(DataImpl<int>*) ret) = stoi(datum.value);
			break;
		case _floatingPoint:
			ret = new DataImpl<double>(datum.funcType);
			(*(DataImpl<double>*) ret) = stod(datum.value);
			break;
		case _boolean:
			ret = new DataImpl<bool>(datum.funcType);
			(*(DataImpl<bool>*) ret) = (datum.value == "true");
			break;
		}

		return ret;
	}

	void parseReflectionTraits(XMLNode def, reflection* ret)
	{
		ret->name = def.getName();
		ret->value = def.getVariable("value");
		ret->dependenceType = getDependenceType(def.getVariable("link"));
		ret->funcType = getFunctionType(def.getVariable("function"));
		ret->primitiveType = getPrimitiveType(def.getVariable("type"));
		ret->good = true;

		if (ret->value == "")
			ret->value = "0";

		if (ret->dependenceType != DP_NONE && ret->funcType == TR_SIMPLE)
			ret->funcType = TR_OFFSET;

		if (ret->dependenceType == DP_NONE && ret->funcType != TR_SIMPLE)
		{
			ret->funcType = TR_SIMPLE;
			//TODO error: variable <name> was defined with non-simple function type but has
			//no dependencies listed. <name>'s function type will be set to simple
		}
	}

	void bindDependencies(reflection* child, reflection* parent)
	{
		bool thisDependsOnParent = (child && child->dependenceType == DP_PARENT);
		bool parentDependsOnThis = (parent && parent->dependenceType == DP_CHILDREN);

		if (thisDependsOnParent || parentDependsOnThis)
		{
			if (!parent)
			{
				//TODO error: child Data depends on NULL parent
				child->good = false;
			}

			else if (!child)
			{
				//TODO error: parent depends on NULL child, but that shouldn't really ever happen 
				//at this point...
				parent->good = false;
			}

			if (child->primitiveType != parent->primitiveType)
			{
				//TODO error: parent and child have inconsistant primitive types
				child->good = false;
			}
		}

		if (child->good)
		{
			if (thisDependsOnParent && !parentDependsOnThis)
			{
				//Add dependency to child
				switch (parent->primitiveType)
				{
				case _integer:
					((DataImpl<int>*)child->pointer)->addDependency(parent->pointer);
					break;
				case _floatingPoint:
					((DataImpl<double>*)child->pointer)->addDependency(parent->pointer);
					break;
				case _boolean:
					((DataImpl<bool>*)child->pointer)->addDependency(parent->pointer);
					break;
				}
			}

			else if (parentDependsOnThis && !thisDependsOnParent)
			{
				//Add dependency to parent
				switch (child->primitiveType)
				{
				case _integer:
					((DataImpl<int>*)parent->pointer)->addDependency(child->pointer);
					break;
				case _floatingPoint:
					((DataImpl<double>*)parent->pointer)->addDependency(child->pointer);
					break;
				case _boolean:
					((DataImpl<bool>*)parent->pointer)->addDependency(child->pointer);
					break;
				}
			}

			else if (thisDependsOnParent && parentDependsOnThis)
			{
				//TODO Error!: circular dependency between parent
				//and child for variable <curTraits.name>
				child->good = false;
			}
		}
	}

#pragma region Get traits by name
	PrimitiveType getPrimitiveType(std::string type)
	{
		if (type.empty() || type == "0" || type == "int" || type == "integer")
			return _integer;
		if (type == "bool" || type == "boolean")
			return _boolean;
		if (type == "float" || type == "floating point")
			return _floatingPoint;
		if (type == "string")
			return _string;
		if (type == "entity")
			return _entity;
		
		return _errorType;
	}

	DependenceType getDependenceType(std::string type)
	{
		if (type.empty() || type == "0" || type == "simple")
			return DP_NONE;
		if (type == "parent")
			return DP_PARENT;
		if (type == "child" || type == "children")
			return DP_CHILDREN;
		else
		{
			//TODO: warning: dependency type <type> is not defined. Dependency type
			// defaulting to no dependencies
			return DP_NONE;
		}
	}

	FuncType getFunctionType(std::string type)
	{
		if (type.empty() || type == "0" || type == "simple")
			return TR_SIMPLE;
		if (type == "sum")
			return TR_SUM;
		if (type == "average")
			return TR_AVERAGE;
		if (type == "offset")
			return TR_OFFSET;
		else
		{
			//TODO: "warning: function type: " + type + " is not defined. Function type defaulting
			//to simple"
			return TR_SIMPLE;
		}
	}
#pragma endregion

#pragma region Get trait names
	std::string getPrimitiveTypeName(PrimitiveType type)
	{
		std::string ret = "";
		switch (type)
		{
		case _integer:
			ret = "integer";
			break;
		case _floatingPoint:
			ret = "floating point";
			break;
		case _boolean:
			ret = "boolean";
			break;
		case _string:
			ret = "string";
			break;
      case _entity:
         ret = "entity";
         break;
		default:
			ret = "error type";
			break;
		}

		return ret;
	}

	std::string getTransformTypeName(FuncType type)
	{
		std::string ret = "";
		switch (type)
		{
		case TR_SIMPLE:
			ret = "simple";
			break;
		case TR_OFFSET:
			ret = "offset";
			break;
		case TR_AVERAGE:
			ret = "average";
			break;
		case TR_SUM:
			ret = "sum";
			break;
		default:
			ret = "undefined transform";
			break;
		}

		return ret;
	}

	std::string getDependenceTypeName(DependenceType type)
	{
		std::string ret = "";
		switch (type)
		{
		case DP_NONE:
			ret = "none";
			break;
		case DP_PARENT:
			ret = "parent";
			break;
		case DP_CHILDREN:
			ret = "children";
			break;
		default:
			ret = "undefined link type";
			break;
		}

		return ret;
	}
#pragma endregion

#pragma region Get Data object sizes
   size_t getDataObjectSize(std::string primitiveType)
   {
       return getDataObjectSize(getPrimitiveType(primitiveType));
   }

   size_t getDataObjectSize(PrimitiveType primitiveType)
   {
       switch (primitiveType)
       {
       case _integer:
           return getDataObjectSize<int>();
       case _floatingPoint:
           return getDataObjectSize<double>();
       case _boolean:
           return getDataObjectSize<bool>();
       default:
           return -1;
       }
   }

#pragma endregion

}
#include "CORE_Factory.h"
#include "Commands.h"
#include "CORE.h"
#include "CORE_Resources.h"
#include "MenuScreen.h"
#include "ControlTypes.h"
#include "ElementTypes.h"
#include "ComponentTypes.h"
#include "Entity.h"

#include <vector>
#include <map>



namespace CORE_Factory
{
	//Private helper functions and structures
	namespace detail
	{
		//Structure containing reflection information for a single datum. Erased once creation of the owning
		//entity is complete
		struct reflection
		{
			int primitiveType;
			int dependenceType;
			int funcType;

			std::string value;
			Data* pointer;
		};

		//Whether the datum depends on its parent, children, or nothing
		enum dependenceTypes
		{
			none = 0,
			parent,
			children,
		};

		//The primitive type underlying the 
		enum primitiveTypes
		{
			_integer,
			_boolean,
			_string,
			_floatingPoint,
			_errorType
		};

		//Enumerates the different function types defining what operations and offsets are applied
		//to the data when accessed 
		enum functionTypes
		{
			simple,
			average,
			sum,
		};

		int getPrimitiveType(std::string type)
		{
			if (type.empty() || type == "0" || type == "int" || type == "integer")
				return _integer;
			if (type == "bool" || type == "boolean")
				return _boolean;
			if (type == "float" || type == "floating point")
				return _floatingPoint;
			if (type == "string")
				return _string;
			else
				return _errorType;
		}

		int getDependenceType(std::string type)
		{
			if (type.empty() || type == "0" || type == "simple")
				return none;
			if (type == "parent")
				return parent;
			if (type == "child" || type == "children")
				return children;
			else
			{
				//TODO: warning: dependency type <type> is not defined. Dependency type
				// defaulting to no dependencies
				return none;
			}
		}

		int getFunctionType(std::string type)
		{
			if (type.empty() || type == "0" || type == "simple")
				return simple;
			if (type == "sum")
				return sum;
			if (type == "average")
				return average;
			else
			{
				//TODO: "warning: function type: " + type + " is not defined. Function type defalting
				//to simple"
				return simple;
			}
		}
	}
	using namespace detail;
#pragma region Object Management

	//Allocate and return a definer for the current node
	//Return a Template if one exists under the current name, a genereic NodeParser if it does not
	Definer* generateDefiner(pugi::xml_node node)
	{
		Definer* ret = NULL;
		std::string nodeName = node.name();

		TemplateDef* templ = CORE_Resources::getTemplate(nodeName);

		if (templ)
		{
			ret = new Template(node, templ);
		}

		else
		{
			ret = new NodeParser(node);
		}

		return ret;
	}

	Component* generateComponent(Definer* def)
	{
		std::string name = def->getName();

		if (name == "iDrawComponent")
		{
			//return new I_DrawComponent(node);
		}

		else if (name == "iVelocityControl")
		{
			return new I_VelocityControl(def);
		}

		else if (name == "position")
		{
			return new Position(def);
		}

		else if (name == "collidable")
		{
			return new Collidable(def);
		}

		else if (name == "mouseProcessor")
		{
			return new MouseProcessor();
		}

		else if (name == "menuDestination")
		{
			return new MenuDestination(def);
		}

		else if (name == "menuLayerAdd")
		{
			return new MenuLayerAdd(def);
		}

		return NULL;
	}

	Control* generateControl(Definer* def)
	{
		std::string name = def->getName();

		if (name == "checkbox")
		{
			return new CheckBoxButton(def);
		}

		else if (name == "dragArea")
		{
			return new DragArea(def);
		}

		else if (name == "GUI_Area")
		{
			return new GUI_Area(def);
		}

		else
		{
			return NULL;
		}
	}

	VisibleElement* generateVisibleElement(Definer* def)
	{
		std::string name = def->getName();

		if (name == "staticTextElement")
		{
			return new StaticTextElement(def);
		}

		else if (name == "variableElement")
		{
			return new VariableElement(def);
		}

		else if (name == "dynamicTextElement")
		{
			return new DynamicTextElement(def);
		}

		else if (name == "imageElement")
		{
			return new ImageElement(def);
		}

		else if (name == "animation")
		{
			return new Animation(def);
		}

		else
		{
			//TODO log error: unsupported type
			return NULL;
		}
	}

	Entity* generateGameObject(Definer* def)
	{

	}

	Entity* generateGameObject(Definer* def, std::map<std::string, reflection>* parentInfo = NULL)
	{
		if (def->getName() == "entity")
		{
			//Allocate a new entity
			Entity* ret = new Entity(def);

			//Get a definer for each datum this entity will hold
			Definer* dataParent = def->getChild("data");
			std::vector<Definer*>* dataNodes = dataParent->getChildren();

			//Map to temporarily store this reflection info for this entity's data
			std::map<std::string, reflection> reflectionInfo;

			//Parse the reflection information 
			for (int i = 0; i < dataNodes->size(); i++)
			{
				Definer* curDef = (*dataNodes)[i];
				reflection newData;

				//Parse reflection info from the node
				std::string name = curDef->getName();
				newData.value = curDef->getVariable("value");
				newData.dependenceType = getDependenceType(curDef->getVariable("dependence"));
				newData.funcType = getFunctionType(curDef->getVariable("function"));
				newData.primitiveType = getPrimitiveType("type");

				if (newData.dependenceType == none && newData.funcType != simple)
				{
					newData.funcType = simple;
					//TODO error: variable <name> was defined with non-simple function type but has
					//no dependencies. <name>'s function type will be set to simple
				}

				//Check new data against data held by the current entity
				if (reflectionInfo.find(name) != reflectionInfo.end())
				{
					reflectionInfo[name] = newData;
				}

				//Perform error checking and notify the developer of any reflection conflicts
				else
				{
					bool add = true;
					reflection oldData = reflectionInfo[name];

					if (oldData.primitiveType != newData.primitiveType)
					{
						//TODO: error: multiple instantiations of variable <name> with conflicting
						//primitive types
						add = false;
					}

					if (oldData.funcType != newData.funcType)
					{
						//TODO error: multiple instantiations of variable <name> with conflicting
						//function types
						add = false;
					}

					if (add && oldData.value != newData.value)
					{
						//TODO warning: multiple instantiations of variable <name> with conflicting
						//values. New value will override old value.
						reflectionInfo[name].value = newData.value;
					}
				}
			}

			//Generate and assign actual data pointers based on the reflection info for each datum
			//Bind dependencies between this and parent
			for (std::map<std::string, reflection>::iterator i = reflectionInfo.begin();
					i != reflectionInfo.end(); ++i)
			{
				std::string curName = i->first;
				reflection cur = i->second;
				cur.pointer = generateDataFromReflection(cur);

				if (parentInfo)
				{
					//Check if this entity's dataum depends on its parent's and vice-versa
					if (parentInfo->find(curName) != parentInfo->end())
					{
						reflection parentReflector = (*parentInfo)[curName];
						bool parentDepends = false;

						//Add this to the parent as a dependency if needed
						if (parentReflector.dependenceType == children)
						{
							//TODO ((*parentInfo)[curName].pointer)-> add the dependency to the parent
							parentDepends = true;
						}

						//Add parent datum to this as a dependency if needed
						if (cur.dependenceType == parent)
						{
							//If the parent depends on this and this depends on
							//the parent, there is a circular dependency
							if (!parentDepends)
							{
								// TODO cur.pointer->addDependency(parentReflector.pointer);
							}

							else
							{
								// TODO Error!: circular dependency between parent
								//and child for variable <curName>
							}
						}


					}
				}
			}

			//Add dependencies as specified by the reflection info for both this and its parent


			//Parse its components

			ret->registerSelf(NULL);
			return ret;
		}

		else
		{
			std::string errorType = "";
			if (!def->getName().empty())
			{
				errorType = def->getName();
			}

			else
			{
				errorType = "<NOT GIVEN>";
			}

			//TODO log error undefined type in xml file
			printf("undefined object type %s in xml file\n", errorType.c_str());
			return NULL;
		}
	}

	Entity* generate(std::string prototypeName)
	{
		//TODO: 
		Entity* objectToSpawn = CORE_Resources::prototypes[prototypeName];

		if (objectToSpawn != NULL)
		{
			Entity* ret = new Entity(*objectToSpawn);
			ret->registerSelf(NULL);
			return ret;
		}

		else
		{
			//TODO
			//throw warning: prototype <prototypeName> does not exist. spawn() returned NULL
			printf("Warning: prototype %s doesn't exist\n", prototypeName.c_str());
			return NULL;
		}
	}

#pragma endregion

	MenuScreen* currentGUI;
	Room* currentRoom;
}
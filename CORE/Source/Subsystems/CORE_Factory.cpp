#include "CORE_Factory.h"
#include "CORE.h"
#include "CORE_Resources.h"
#include "MenuScreen.h"
#include "ControlTypes.h"
#include "ElementTypes.h"
#include "ComponentTypes.h"
#include "Entity.h"
#include "Handler.h"
#include "DataSource.h"
#include "Node.h"
#include "ScriptEventHandler.h"
#include "EntityScriptEventHandler.h"

#include <vector>
#include <map>

using namespace CORE_TypeTraits;

namespace CORE_Factory
{
#pragma region Object Management
/**
	Function: generateNode
	
	Allocate and return a definer for the current node
	Return a NodeTemplate if one exists under the current name, a genereic XMLNode if it does not
*/
	XMLNode generateNode(pugi::xml_node node)
	{
		XMLNode ret;
		std::string nodeName = node.name();

		TemplateDef* templ = CORE_Resources::getTemplate(nodeName);

		if (templ)
		{
			ret = XMLNode(templ->invoke(node));
		}

		else
		{
			ret = XMLNode(node);
		}

		return ret;
	}

#pragma region Component Constructor Mapping
	Component* generateComponent(XMLNode def)
	{
		std::string name = def.getName();

		Component* ret = NULL;

		if (name == "iVelocityControl")
			ret = new I_VelocityControl();

		else if (name == "position")
			ret = new Position(def);

		else if (name == "collidable")
			ret = new Collidable(def);

		else if (name == "mouseProcessor")
			ret = new MouseProcessor();

		else if (name == "menuDestination")
			ret = new MenuDestination();

		else if (name == "menuLayerAdd")
			ret = new MenuLayerAdd();

		else if (name == "StandardCollision")
			ret = new StandardCollision();

		else if (name == "Handler")
		  ret = new Handler();
		return ret;
	}

	Control* constructControl(XMLNode def)
	{
		std::string name = def.getName();

		Control* ret = NULL;

		if (name == "checkbox")
			ret = new CheckBoxButton();

		else if (name == "dragArea")
			ret = new DragArea();

		else if (name == "GUI_Area")
			ret = new GUI_Area();

		return ret;
	}

	VisibleElement* constructVisibleElement(XMLNode def)
	{
		std::string name = def.getName();

		VisibleElement* ret = NULL;

		if (name == "staticTextElement")
			ret = new StaticTextElement();

		else if (name == "variableElement")
			ret = new VariableElement();

		else if (name == "dynamicTextElement")
			ret = new DynamicTextElement();

		else if (name == "imageElement")
			ret = new ImageElement();

		else if (name == "animation")
			ret = new Animation();

		else
		{
			//TODO log error: unsupported type
		}

		return ret;
	}

	Component* constructComponent(XMLNode def)
	{
		Component* ret = NULL;

		if (ret = generateComponent(def))
			return ret;
		if (ret = constructControl(def))
			return ret;
		if (ret = constructVisibleElement(def))
			return ret;
		if (def.getName() == "entity")
			ret = new Entity();

		return ret;
	}

	EventHandler* constructEventHandler(XMLNode def)
	{
		EventHandler* ret = NULL;
		
		std::string type =  def.getVariable("type");
		
		if (type == "script")
		{
			ret = new ScriptEventHandler(def);
		}
		
		else if (type == "entityScript")
		{
			ret = new EntityScriptEventHandler(def);
		}
		
		//Add new cases as new hard-coded event handlers are added
		
		if (!ret)
		{
			CORE_SystemIO::error("EventHandler XMLNode \'" + def.getName() + "\' is of an undefined type");
		}
		
		return ret;
	}
#pragma endregion

#pragma region Game Object Generation
	
	/**
	Function: generateObject
	
	Purpose:
		Instantiate and return a copy of an existing prototype
	*/
	Component* generateObject(XMLNode def, DataSource* parentData)
	{
		Component* ret = constructComponent(def);

		if (ret)
		{
			//Set to false if something goes wrong and ret cannot be safely generated
			bool good = true;

			//Get the 'data' node and generate a DataSource from it for the current component parse
			XMLNode dataNode = def.getChild("data");


			DataSource currentSource = DataSource(&dataNode, parentData);

			ret->get_data(&currentSource);

			//Set up event handlers
			XMLNode eventsNode = def.getChild("eventHandlers");

			if (!eventsNode.null())
			{
				ret->getEventHandlers(eventsNode);
			}

			//Pass the definer* to the component for it to get raw text values from free child nodes
			ret->getText(def);
         
			//XMLNode handlerChild = def.getChild("eventHandlers");
			//
			//if (!handlerChild.null())
			//{
			//	ret->getEventHandlers(handlerChild);
			//}

			#pragma region Child Components
			//Get the Components node from definer*
			XMLNode componentsParent = def.getChild("components");

			//Generate components from the components node
			if (!componentsParent.null())
			{
				if (!ret->isBasicComponent())
				{
					std::vector<XMLNode> componentsVector = componentsParent.getChildren();
					for (unsigned int i = 0; i < componentsVector.size(); i++)
					{
						XMLNode curComponentDef = componentsVector[i];
						Component* newComponent = constructComponent(curComponentDef);
						
						newComponent->parent = (Entity*) ret;

						newComponent = generateObject(curComponentDef, &currentSource);

						//TODO Will need to delete and NULL ret if something goes wrong
						if (newComponent)
						{
							ret->storeChild(newComponent);
						}
					}
				}

				else
				{
					//TODO error: 
					CORE_SystemIO::error("Definer for object of type: " +  def.getName() + 
						" contains components node, but type is basic component.");
				}
			}
			#pragma endregion

			//Finalize the component if this is a root call
			if (!parentData)
			{
				//TODO null parent info means this is root. finalize it from top to bottom
			}

			//Return NULL component rather than an invalid one
			if (!good)
			{
				delete ret;
				ret = NULL;
		   }
	   }

		//Component was of undefined type
		else
		{
			std::string errorType = "";
			if (!def.getName().empty())
				errorType = def.getName();
			
			else
				errorType = "<NOT GIVEN>";
			
			//TODO log error undefined type in xml file
			printf("undefined object type %s in xml file\n", errorType.c_str());
		}

		return ret;
	}

	/**
	Function: generate
	
	Purpose:
		Generate an instance of the prototype of the given name
	*/
	Entity* generate(std::string prototypeName)
	{
		//TODO: 
		Entity* objectToSpawn = CORE_Resources::prototypes[prototypeName];

		if (objectToSpawn != NULL)
		{
			Entity* ret = new Entity(*objectToSpawn);
			return ret;
		}

		else
		{
			CORE_SystemIO::error("Warning: prototype " + prototypeName + " doesn't exist\n");
			return NULL;
		}
	}

	//
	State* generateState(XMLNode definer)
	{
		State* ret = new State();
		DataSource source = DataSource(&definer, NULL);
		std::vector<std::pair<std::string, reflection>> data = source.getAllData();
		
		for (unsigned int i = 0; i < data.size(); i++)
		{
			ret->addData(data[i].first, data[i].second.pointer);
		}
		
		return ret;
	}
#pragma endregion
}
#include "CORE_Factory.h"
#include "CORE.h"
#include "CORE_Resources.h"
#include "MenuScreen.h"
#include "ControlTypes.h"
#include "ElementTypes.h"
#include "ComponentTypes.h"
#include "Entity.h"
#include "DataSource.h"
#include "NodeTemplate.h"
#include "DefaultNode.h"

#include <vector>
#include <map>

using namespace CORE_TypeTraits;

namespace CORE_Factory
{
#pragma region Object Management
	//Allocate and return a definer for the current node
	//Return a NodeTemplate if one exists under the current name, a genereic DefaultNode if it does not
	Node* generateNode(pugi::xml_node node)
	{
		Node* ret = NULL;
		std::string nodeName = node.name();

		TemplateDef* templ = CORE_Resources::getTemplate(nodeName);

		if (templ)
		{
			ret = new NodeTemplate(node, templ);
		}

		else
		{
			ret = new DefaultNode(node);
		}

		return ret;
	}

#pragma region Component Constructor Mapping
	Component* generateComponent(Node* def)
	{
		std::string name = def->getName();

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

		return ret;
	}

	Control* constructControl(Node* def)
	{
		std::string name = def->getName();

		Control* ret = NULL;

		if (name == "checkbox")
			ret = new CheckBoxButton();

		else if (name == "dragArea")
			ret = new DragArea();

		else if (name == "GUI_Area")
			ret = new GUI_Area();

		return ret;
	}

	VisibleElement* constructVisibleElement(Node* def)
	{
		std::string name = def->getName();

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

	Component* constructComponent(Node* def)
	{
		Component* ret = NULL;

		if (ret = generateComponent(def))
			return ret;
		if (ret = constructControl(def))
			return ret;
		if (ret = constructVisibleElement(def))
			return ret;
		if (def->getName() == "entity")
			ret = new Entity();

		return ret;
	}
#pragma endregion

#pragma region Game Object Generation
	//Recursively parse an entity/component and its children from a node
	Component* generateObject(Node* def, DataSource* parentData)
	{
		Component* ret = constructComponent(def);

		if (ret)
		{
			//Set to false if something goes wrong and ret cannot be safely generated
			bool good = true;

			//Get the 'data' node and generate a DataSource from it for the current component parse
			Node* dataNode = def->getChild("data");
			DataSource currentSource = DataSource(dataNode, parentData);

			ret->get_data(&currentSource);

         //Set up event handlers
         Node* eventsNode = def->getChild("eventHandlers");


			//Pass the definer* to the component for it to get raw text values from free child nodes
			ret->getText(def);

			#pragma region Child Components
			//Get the Components node from definer*
			Node* componentsParent = def->getChild("components");

			//Generate components from the components node
			if (componentsParent)
			{
				if (!ret->isBasicComponent())
				{
					std::vector<Node*>* componentsVector = componentsParent->getChildren();
					for (unsigned int i = 0; i < componentsVector->size(); i++)
					{
						Node* curComponentDef = (*componentsVector)[i];
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
					//TODO error: definer for object of type def->getName() contains components node, but
					//type is basic component with no child components. Components will be ignored
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
         if (!def->getName().empty())
            errorType = def->getName();
         
         else
            errorType = "<NOT GIVEN>";
         
         //TODO log error undefined type in xml file
         printf("undefined object type %s in xml file\n", errorType.c_str());
      }

		return ret;
	}

	//Return a copy of a preexisting prototype
	Entity* generate(std::string prototypeName)
	{
		//TODO: 
		Entity* objectToSpawn = CORE_Resources::prototypes[prototypeName];

		if (objectToSpawn != NULL)
		{
			Entity* ret = new Entity(*objectToSpawn);
			ret->registerEvents(NULL);
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

   //
   State* generateState(Node* definer)
   {
      State* ret = new State();
      DataSource source = DataSource(definer, NULL);
      std::vector<std::pair<std::string, reflection>> data = source.getAllData();

      for (int i = 0; i < data.size(); i++)
      {
         ret->addData(data[i].first, data[i].second.pointer);
      }

      return ret;
   }
#pragma endregion
}
#include "Component.h"
#include "Entity.h"
#include "CORE_Resources.h"

#include <cstring>

#pragma region Creational
Component::Component()
{
	ID = std::to_string((rand() << 0) | rand());
}

void Component::storeChild(Component* child)
{
	//warning TODO error: attempted to add child component to basic component. Child will not be added
}

Component* Component::spawnCopy()
{
	printf("warning: spawnCopy should not have been called, please overload\n");
	return NULL;
}

void Component::finalize() {}

//Component gets no data or text by default
void Component::getText(Node* def) {}

void Component::get_data(DataSource* source) {}

//Component gets only the event handlers assigned to it in the file. Subclasses may have handlers baked in
void Component::getEventHandlers(Node* def)
{
    if (!def)
    {
        CORE_SystemIO::error("Could not get Event Handlers from null Node*");
        return;
    }

    std::vector<Node*>* handlerVector = def->getChildren();
   
    //Iterate over each event definition in the node
    for (int i = 0; i < handlerVector->size(); i++)
    {
        Node* cur = (*handlerVector)[i];

        std::string eventName = cur->getName();
        EventDef curDef;
        
        if (CORE_Resources::events.find(eventName) != CORE_Resources::events.end())
        {
           curDef = CORE_Resources::events[eventName];
           std::vector<Node*>* handlers = cur->getChildren();

           //Add a handler for each entry in the event node
           for (int j = 0; j < handlers->size(); j++)
           {
              Node* curHandler = (*handlers)[j];
              std::string handlerName = curHandler->getName();

              if (CORE_Resources::eventHandlers.find(handlerName) != CORE_Resources::eventHandlers.end())
              {
                 if (CORE_Resources::eventHandlers[handlerName]->
                    matches(CORE_Resources::events[eventName]))
                 {
                    eventHandlers[handlerName].push_back(CORE_Resources::eventHandlers[handlerName]);
                 }

                 else
                    CORE_SystemIO::error("EventHandler \'" + handlerName +
                       "\' does not match EventDef " + eventName);
                    
              }

              else
                 CORE_SystemIO::error("Event handler \'" + handlerName + "\' does not exist");
           }
           
        }

        //Handlers can only be assigned for predefined events
        else
           CORE_SystemIO::error("Event \'" + eventName + "\' does not exist");
    }
}

#pragma endregion

#pragma region Type Reflection

bool Component::isBasicComponent()
{
	return false;
}
#pragma endregion

#pragma region Parent Registration
void Component::registerEvents(Entity* newParent)
{
	if (!parent)
	{
		printf("NULL parent\n");
		return;
	}

	for (unsigned int i = 0; i < events.size(); i++)
	{
		parent->addListener(events[i], this);
	}
}
#pragma endregion

//void* Component::findAncestorPointer(std::string name) const
//{
//	void* temp = NULL;
//
//	if (parent)
//	{
//		temp = parent->findPointer(name);
//
//		if (!temp)
//		{
//			return parent->findAncestorPointer(name);
//		}
//	}
//
//	return temp;
//}
#include "Component.h"
#include "EventHandler.h"
#include "MessagePasser.h"
#include "Entity.h"
#include "CORE_Resources.h"
#include "CORE.h"

#include <cstring>

#pragma region Creational
Component::Component() {
	events.push_back(updateStep);
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
void Component::getText(XMLNode def) {}

void Component::get_data(DataSource* source) {}

// Get a trait from this component. Components have no traits by default
bool Component::getTrait(std::string trait)
{
	return false;
}

//Component gets only the event handlers assigned to it in the file. 
//Subclasses may have handlers baked in
void Component::getEventHandlers(XMLNode def)
{
	if (def.null())
	{
		CORE_SystemIO::error("Could not get Event Handlers from null XMLNode*");
		return;
	}

	std::vector<XMLNode> handlerVector = def.getChildren();

	//Iterate over each event definition in the node
	for (unsigned int i = 0; i < handlerVector.size(); i++)
	{
		XMLNode cur = handlerVector[i];

		std::string eventName = cur.getName();
		EventDef curDef;
		
		if (CORE_Resources::events.find(eventName) != CORE_Resources::events.end())
		{
			curDef = CORE_Resources::events[eventName];
			std::vector<XMLNode> handlers = cur.getChildren();

			//Add a handler for each entry in the event node
			for (int j = 0; j < handlers.size(); j++)
			{
				XMLNode curHandler = handlers[j];
				std::string handlerName = curHandler.getName();
				int curEventOpcode = CORE_Resources::getEventCode(eventName);
				EventHandler* eventHandler = 
				 CORE_Resources::getEventHandler(handlerName);

				if (eventHandler)
				{
					if (eventHandler->matches(CORE_Resources::events[eventName]))
					{
						eventHandlers[curEventOpcode].push_back ( eventHandler );
						eventHandler->registerOwner( getContext() );
					}

					else
					{
						CORE_SystemIO::error("EventHandler \'" + handlerName +
							"\' does not match EventDef " + eventName);
					}
				}

				else
				{
					CORE_SystemIO::error(
					"Event handler \'" + handlerName + "\' does not exist");
				}
			}
		}

		//Handlers can only be assigned for predefined events
		else
		{
			CORE_SystemIO::error("Event \'" + eventName + "\' does not exist");
		}
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

/**
	Function: handle

	Purpose:
		Handle the given event
*/
void Component::handle(Event e) {}

void Component::condReceive(Event e, Entity* ancestor)
{
	if (isAncestor(ancestor))
	{
		receive(e);
	}
}

void Component::registerEv(MessagePasser* passer)
{
	if (!passer)
	{
		printf("cannot register to NULL room\n");
		return;
	}

	for (unsigned int i = 0; i < events.size(); i++)
	{
		passer->registerEvent(events[i], this);
	}

	for (std::map<int, std::vector<EventHandler*>>::iterator it = eventHandlers.begin(); it != eventHandlers.end(); ++it)
	{
		
		std::vector<EventHandler*>& vec = it->second;
		for (int i = 0; i < vec.size(); i++)
		{
			passer->registerEvent(it->first, vec[i]);
		}
			
	}
}

#pragma endregion

Entity* Component::getContext()
{
	return parent;
}

// Check 
bool Component::isAncestor(Component* toCheck)
{
	if (this == toCheck) {
		return true;
	}

	else if (parent == NULL) {
		return false;
	}

	else {
		return parent->isAncestor(toCheck);
	}
}

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
#pragma once
#include "QuadTree.h"
#include "Collidable.h"
#include "MenuScreen.h"
#include "Room.h"
#include "State.h"
#include "DataSource.h"
#include "Node.h"

#include <stdlib.h>
#include <vector>
#include <map>

/*
CORE_Factory subsystem
	Purpose:
		1. Expose a public API for generating various engine objects by name rather than by
			calling a specific constructor or factory method
		2. Decouple the specific implementations of engine objects from the implementations
			that depend on them
		3. Abstract the XML parsing module away from the rest of the engine
		4. Check for and resolve errors in user-defined objects such as type
			inconsistancies, uninitialized variables, and malformed prototype
			definitions to isolate the lower-leve engine from user errors

XML Parser, currently part of CORE_Factory implementation
	Purpose: provide an XML parsing interface in order to:
		1. Decouple CORE_Factory from any specific XML library
		2. Parse XML files to a common node format from which CORE_Factory
			can generate engine objects.
		3. Provide polymorphism in node objects to allow nodes with similar public interfaces
			to be formed from nodes with differeing internal structures (eg. templates - see Template.h)
*/
namespace CORE_Factory
{
	//Generation helpers
	XMLNode generateNode(pugi::xml_node node);

	std::string getAlias(std::string alias);

	//Constructor mapping
	Control* constructControl(XMLNode definer);
	VisibleElement* constructVisibleElement(XMLNode definer);
	Component* generateComponent(XMLNode definer);
	Component* constructComponent(XMLNode def);
	EventHandler* constructEventHandler(XMLNode def);

	//ObjectGeneration
	Entity* generate(std::string prototypeName);
	State* generateState(XMLNode definer);
	Component* generateObject(XMLNode definer, DataSource* parentData = NULL);
};
#pragma once
#include "Component.h"
#include "Node.h"

class MenuLayerAdd : public Component
{
public:
	MenuLayerAdd();
	void MenuLayerAdd::getText(XMLNode def);

   virtual void handle(Event e);

protected:
	std::string source;
};
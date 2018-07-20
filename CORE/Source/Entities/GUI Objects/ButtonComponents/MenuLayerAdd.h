#pragma once
#include "Component.h"
#include "DefaultNode.h"

class MenuLayerAdd : public Component
{
public:
	MenuLayerAdd();
	void MenuLayerAdd::getText(DefaultNode* def);

   virtual void handle(Event e);

protected:
	std::string source;
};
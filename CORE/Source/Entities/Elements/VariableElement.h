#pragma once

#include "VisibleElement.h"
#include <map>


class VariableElement : public VisibleElement
{
public:
	VariableElement();
	VariableElement(VariableElement&);
	virtual Component* spawnCopy();
	virtual void getText(XMLNode def);


   virtual void handle(Event e);
	virtual void draw();

	std::map<std::string, VisibleElement*> elements;
	VisibleElement* current;

	void setTexture(std::string name);
};
#pragma once

#include "VisibleElement.h"
#include <map>


class VariableElement : public VisibleElement
{
public:
	VariableElement();
	VariableElement(VariableElement&);
	virtual Component* spawnCopy();
	virtual void getText(Node* def);


	virtual void handleInput(int key, int upDown = 0, int x = 0, int y = 0);
	virtual void draw();

	std::map<std::string, VisibleElement*> elements;
	VisibleElement* current;

	void setTexture(std::string name);
};
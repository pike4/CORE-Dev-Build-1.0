#pragma once
#include "Node.h"
#include "Component.h"
#include "RenderableCharSet.h"

#include "SDL.h"

class VisibleElement : public Component
{
public:
	DataImpl<int>* x;
	DataImpl<int>* y;

	DataImpl<int>* zIndex;

	VisibleElement();
	VisibleElement(int aX, int aY, int aW, int aH);
	VisibleElement(VisibleElement& copy);

	virtual void get_data(DataSource* source);
	virtual void getText(XMLNode def);

   void handle(Event e);

	virtual void move(int x, int y);

	virtual Component* spawnCopy() = 0;
	virtual void draw() = 0;

protected:
	int w;
	int h;
};
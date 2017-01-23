#pragma once
#include "Definer.h"
#include "Component.h"
#include "SDL.h"
#include "RenderableCharSet.h"

class VisibleElement : public Component
{
public:
	DataOffset<int>* X;
	DataOffset<int>* Y;
	VisibleElement();
	VisibleElement(int x, int y, int w, int h);
	VisibleElement(Definer* definer);
	VisibleElement(VisibleElement& copy);

	void handleInput(int key, int upDown = 0, int x = 0, int y = 0);

	virtual void assignPointers(Entity* aParent);
	virtual void move(int x, int y);

	virtual Component* spawnCopy() = 0;
	virtual void draw() = 0;

protected:



	int w;
	int h;
};
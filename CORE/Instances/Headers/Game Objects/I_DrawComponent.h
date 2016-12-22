#pragma once
#include "Component.h"
#include "Entity.h"
#include "CompositeDrawable.h"
#include "pugixml.hpp"

/*class I_DrawComponent : virtual public Entity, virtual public CompositeDrawable
{
public:
	I_DrawComponent();
	I_DrawComponent(I_DrawComponent& other);
	I_DrawComponent(pugi::xml_node node);
	void assignPointers(Entity* parent);

	//virtual Component* spawnCopy();
	virtual void handleInput(int key, int upDown = 0, int x = 0, int y = 0);

private:
	int* x;
	int* y;

	CompositeDrawable* drawable;
};*/
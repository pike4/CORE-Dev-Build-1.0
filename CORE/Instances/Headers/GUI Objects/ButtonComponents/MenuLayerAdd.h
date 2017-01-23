#pragma once
#include "Component.h"
#include "Definer.h"

class MenuLayerAdd : public Component
{
public:
	MenuLayerAdd();
	MenuLayerAdd(Definer* definer);
	virtual void handleInput(int key, int upDown = 0, int x = 0, int y = 0);

protected:
	std::string source;
};
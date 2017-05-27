#pragma once
#include "Component.h"
#include "Node.h"

class MenuLayerAdd : public Component
{
public:
	MenuLayerAdd();
	void MenuLayerAdd::getText(Node* def);

	virtual void handleInput(int key, int upDown = 0, int x = 0, int y = 0);

protected:
	std::string source;
};
#pragma once
#include "Component.h"
class Position : public Component
{
public:
	void assignPointers(GameObject* parent);
private:
	int* x;
	int* y;
};
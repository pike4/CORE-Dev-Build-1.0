#include "Position.h"
#include "GameObject.h"

void Position::assignPointers(GameObject* parent)
{
	x = (int*) parent->getPointer("x", sizeof(int));
	y = (int*) parent->getPointer("x", sizeof(int));
}
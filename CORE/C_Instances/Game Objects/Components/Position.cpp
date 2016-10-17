#include "Position.h"
#include "GameObject.h"

void Position::assignPointers(GameObject* parent)
{
	x = (int*) parent->getPointer("x", sizeof(int));
	y = (int*) parent->getPointer("y", sizeof(int));
}

void Position::handleInput(int key, int upDown, int x, int y)
{
	switch (key)
	{
	case updateStep:

		break;
	}
}
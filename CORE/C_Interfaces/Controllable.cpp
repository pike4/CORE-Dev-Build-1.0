#include "Controllable.h"
#include <vector>

Controllable::Controllable(std::vector<Controllable*>* controllableVector)
{
	controllableVector->push_back(this);
}

Controllable::Controllable() {}
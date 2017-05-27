#pragma once
#include "Transform.h"

template <typename T>
class TR_Simple : public Transform<T>
{
public:
	virtual T get(const DataImpl<T>* owner, int count)
	{
		return owner->value;
	}
};
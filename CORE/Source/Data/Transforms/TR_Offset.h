#pragma once
#include "Transform.h"

template <typename T>
class TR_Offset : public Transform<T>
{
public:
	virtual T get(const DataImpl<T>* owner, int count)
	{
		DataImpl<T>** values = owner->data;
		T ret = owner->value;

		for (int i = 0; i < count; i++)
		{
			ret += *values[i];
		}

		return ret;
	}
};
#pragma once
#include "Transform.h"

template <typename T>
class TR_Sum : public Transform<T>
{
public:
	virtual T get(const DataImpl<T>* owner, int count)
	{
		DataImpl<T>** values = owner->data;
		T ret = 0;

		for (int i = 1; i < count; i++)
		{
			ret += *values[i];
		}

		return ret;
	}
};
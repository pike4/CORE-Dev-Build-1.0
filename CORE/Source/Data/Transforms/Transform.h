#pragma once
#include "Data.h"

template<typename T>
class Transform
{
public:
	virtual T get(const DataImpl<T>* owner, int count) = 0;
};
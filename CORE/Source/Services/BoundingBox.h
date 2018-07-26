#pragma once
#include <Data.h>

struct BoundingBox
{
	Entity*			e;
	DataImpl<int>*	x;
	DataImpl<int>*	y;
	DataImpl<int>*	w;
	DataImpl<int>*	h;
};
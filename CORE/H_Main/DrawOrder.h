#pragma once
#include "SDL.h"
typedef SDL_Texture* texture;
typedef struct _drawOrder drawOrder;

struct _drawOrder
{
	int x;
	int y;
	texture tex;
	int zIndex;

	bool operator < (const drawOrder& d2) const
	{
		return (zIndex < d2.zIndex);
	}
};
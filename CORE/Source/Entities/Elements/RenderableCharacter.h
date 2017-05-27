#pragma once
#include "SDL.h"
#include "SDL_TTF.h"

//This is a resource, not a component
class RenderableCharacter
{
public:
	int x, y, w, h;

	SDL_Texture* character;

	RenderableCharacter(char, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer);
};
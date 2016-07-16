#pragma once
#include "RenderableCharacter.h"
#include "SDL_TTF.h"
#include <string>

class RenderableCharSet
{
public:
	SDL_Texture* charSet[256];
	RenderableCharSet(int a_fontSize, TTF_Font* a_font, SDL_Color a_color, SDL_Renderer* a_Renderer);
	std::string name;
	int fontWidth, fontHeight;

private:
	int fontSize;
	TTF_Font* font;
	SDL_Color color;
};
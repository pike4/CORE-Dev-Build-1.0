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
	int fontWidth(int index);
	int fontHeight;

	SDL_Texture* operator[](int index);

private:
	int fontSize;
	int fontWidths[256];
	TTF_Font* font;
	SDL_Color color;
};
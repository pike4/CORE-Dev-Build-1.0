#include "RenderableCharacter.h"

RenderableCharacter::RenderableCharacter(char a_character, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer)
{
	character = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Solid(font, &a_character, color));
	SDL_QueryTexture(character, NULL, NULL, &w, &h);
}
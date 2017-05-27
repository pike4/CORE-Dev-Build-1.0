#include "RenderableCharset.h"

RenderableCharSet::RenderableCharSet(int a_fontSize, TTF_Font* a_font, SDL_Color a_color, SDL_Renderer* a_renderer)
{
	fontSize = a_fontSize;
	font = a_font;
	color = a_color;
	std::string a = "";

	for (int x = 0; x < 256; x++)
	{
		a += (char)x;
		charSet[x] = SDL_CreateTextureFromSurface(a_renderer, TTF_RenderText_Solid(a_font, a.c_str(), a_color));
		SDL_QueryTexture(charSet[x], NULL, NULL, fontWidths + x, NULL);

		a = "";
	}

	SDL_QueryTexture(charSet[1], NULL, NULL, NULL, &fontHeight);
}

SDL_Texture* RenderableCharSet::operator[](int index)
{
	return charSet[index % 256];
}

int RenderableCharSet::fontWidth(int index)
{
	return fontWidths[index % 256];
}
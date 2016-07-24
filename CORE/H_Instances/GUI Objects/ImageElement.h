#pragma once
#include "VisibleElement.h"

class ImageElement : public VisibleElement
{
public:
	SDL_Texture* texture;

	ImageElement(int x, int y, int w, int h, SDL_Texture* texture);
	ImageElement(pugi::xml_node node);
	ImageElement(ImageElement& copy);

	virtual void draw(SDL_Renderer* renderer);

private:
	void getArgsFromNode(pugi::xml_node node);
};
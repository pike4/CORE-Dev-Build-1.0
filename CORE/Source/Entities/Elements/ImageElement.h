#pragma once
#include "VisibleElement.h"

class ImageElement : public VisibleElement
{
public:
	SDL_Texture* texture;
	ImageElement();
	ImageElement(int x, int y, int w, int h, SDL_Texture* texture);
	ImageElement(ImageElement& copy);

	void ImageElement::getText(DefaultNode* definer);

   virtual void handle(Event e);

	virtual Component* spawnCopy();
	virtual void draw();

private:
};
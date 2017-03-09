#pragma once
#include "VisibleElement.h"

class ImageElement : public VisibleElement
{
public:
	SDL_Texture* texture;
	ImageElement();
	ImageElement(int x, int y, int w, int h, SDL_Texture* texture);
	ImageElement(ImageElement& copy);

	void ImageElement::getText(Node* definer);

	virtual void handleInput(int key, int upDown = 0, int x = 0, int y = 0);

	virtual Component* spawnCopy();
	virtual void draw();

private:
	void getArgsFromNode(Node* definer);
};
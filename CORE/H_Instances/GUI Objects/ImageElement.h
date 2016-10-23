#pragma once
#include "VisibleElement.h"

class ImageElement : public VisibleElement
{
public:
	SDL_Texture* texture;

	ImageElement(int x, int y, int w, int h, SDL_Texture* texture);
	ImageElement(pugi::xml_node node);
	ImageElement(ImageElement& copy);

	virtual void handleInput(int key, int upDown = 0, int x = 0, int y = 0);

	virtual Component* spawnCopy();
	virtual void draw();

private:
	void getArgsFromNode(pugi::xml_node node);
};
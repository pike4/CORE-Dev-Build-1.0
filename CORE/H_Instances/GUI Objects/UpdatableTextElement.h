#pragma once
#include "TextElement.h"
#include <string>

class UpdatableTextElement : public TextElement
{
public:
	UpdatableTextElement(int x, int y, int w, int h, RenderableCharSet* charSet);
	UpdatableTextElement(pugi::xml_node node);

	void setText(std::string newText);
	void append(std::string addition);

	virtual void draw(SDL_Renderer* renderer);

private:
	int currentLineindex;
};
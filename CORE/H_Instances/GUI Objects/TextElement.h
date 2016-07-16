#pragma once
#include "VisibleElement.h"
#include <string>
#include <vector>

class TextElement : public VisibleElement
{
public:
	std::string text;
	std::vector<std::string> lines;


	TextElement(int x, int y, int w, int h, RenderableCharSet* charSet);
	TextElement(pugi::xml_node node);
	TextElement(TextElement& copy);

	virtual void draw(SDL_Renderer* renderer);
	void stringToLines(std::string message);

private:
	RenderableCharSet* charSet;

	//The max number of characters that can go into a line
	int maxLineLength;
};
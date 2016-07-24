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
	TextElement(int x, int y, int w, int h, RenderableCharSet* charSet, std::string text);
	TextElement(pugi::xml_node node);
	TextElement(TextElement& copy);

	virtual void draw(SDL_Renderer* renderer);
	void stringToLines(std::string message);

private:
	RenderableCharSet* charSet;

	//The max number of characters that can go into a line
	int maxLineLength;

	//The maximum number of lines that can be displayed within the bounds
	int maxLines;

	//The index of the line to start drawing from
	int lineIndex;

	void getArgsFromNode(pugi::xml_node);
};
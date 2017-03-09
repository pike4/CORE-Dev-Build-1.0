#pragma once
#include "VisibleElement.h"
#include <string>
#include <vector>

class StaticTextElement : public VisibleElement
{
public:
	std::string text;
	std::vector<std::string> lines;

	StaticTextElement(int x, int y, int w, int h, RenderableCharSet* charSet);
	StaticTextElement(int x, int y, int w, int h, RenderableCharSet* charSet, std::string text);
	StaticTextElement();
	StaticTextElement(StaticTextElement& copy);

	void getText(Node* definer);

	void stringToLines(std::string message);

	virtual VisibleElement* spawnCopy();

	virtual void draw();

private:
	RenderableCharSet* charSet;

	//The max number of characters that can go into a line
	unsigned int maxLineLength;

	//The maximum number of lines that can be displayed within the bounds
	unsigned int maxLines;

	//The index of the line to start drawing from
	unsigned int lineIndex;
};
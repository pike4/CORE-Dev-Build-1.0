#pragma once
#include "StaticTextElement.h"
#include <string>

class DynamicTextElement : public StaticTextElement
{
public:
	DynamicTextElement(int x, int y, int w, int h, RenderableCharSet* charSet);
	DynamicTextElement();

	void setText(std::string newText);
	void append(std::string addition);

	virtual void draw();

private:
	int currentLineindex;
};
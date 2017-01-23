#include "DynamicTextElement.h"
#include "StaticTextElement.h"

DynamicTextElement::DynamicTextElement(int x, int y, int w, int h, RenderableCharSet* charSet)
	: StaticTextElement(x, y, w, h, charSet)
{
	currentLineindex = 0;
}

DynamicTextElement::DynamicTextElement(Definer* definer)
	: StaticTextElement(definer)
{

}

void DynamicTextElement::setText(std::string newText)
{
	lines.clear();
	text = newText;
	stringToLines(newText);
}

void DynamicTextElement::append(std::string addition)
{
	lines.clear();
	text.append(addition);
	stringToLines(text);
}

void DynamicTextElement::draw()
{
	StaticTextElement::draw();
}
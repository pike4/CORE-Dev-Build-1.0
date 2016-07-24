#include "UpdatableTextElement.h"
#include "TextElement.h"

UpdatableTextElement::UpdatableTextElement(int x, int y, int w, int h, RenderableCharSet* charSet)
	: TextElement(x, y, w, h, charSet)
{
		int ihawihw = this->box.x;
	currentLineindex = 0;
}

UpdatableTextElement::UpdatableTextElement(pugi::xml_node node)
	: TextElement(node)
{

}

void UpdatableTextElement::setText(std::string newText)
{
	lines.clear();
	text = newText;
	stringToLines(newText);
}

void UpdatableTextElement::append(std::string addition)
{
	lines.clear();
	text.append(addition);
	stringToLines(text);
}

void UpdatableTextElement::draw(SDL_Renderer* renderer)
{
	TextElement::draw(renderer);
}
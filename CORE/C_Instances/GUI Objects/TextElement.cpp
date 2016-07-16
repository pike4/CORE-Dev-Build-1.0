#include "TextElement.h"
#include "VideoManager.h"

TextElement::TextElement(int x, int y, int w, int h, RenderableCharSet* charSet)
	:VisibleElement(x, y, w, h)
{
	this->charSet = charSet;

	maxLineLength = box.w / charSet->fontWidth;
}
TextElement::TextElement(pugi::xml_node node)
	:VisibleElement(node)
{
	text = node.child("text").first_child().value();
}

TextElement::TextElement(TextElement& copy)
	:VisibleElement(copy)
{
	
}

void TextElement::draw(SDL_Renderer* renderer)
{
	int penX = box.x;
	int penY = box.y;

	for (int x = 0; x < lines.size(); x++)
	{
		for (int y = 0; y < lines[x].length(); y++)
		{
			VideoManager::applyTexture(penX, penY, renderer, charSet->charSet[lines[x][y]]);
			penX += charSet->fontWidth;
		}

		penY += charSet->fontHeight;
		penX = box.x;
	}
}

void TextElement::stringToLines(std::string message)
{
	int length = message.length();
	std::vector<std::string> words;

	std::string buffer = "";

	//Convert given char* to vector of char* words
	for (int x = 0; x < length; x++)
	{
		if (message[x] != ' ')
		{
			buffer += message[x];
		}

		else if (buffer.compare(""))
		{
			words.push_back(buffer);
			buffer = "";
		}
	}

	if (buffer.compare(""))
	{
		words.push_back(buffer);
	}
	buffer = "";

	//Push down words onto lines vector so they wrap
	for (int x = 0; x < words.size(); x++)
	{
		if (words[x].length() + buffer.length() < maxLineLength)
		{
			buffer += words[x] + " ";
		}

		else if (words[x].length() < maxLineLength)
		{
			lines.push_back(buffer);
			buffer = "";
			x--;
		}

		else
		{
			lines.push_back(buffer.substr(0, maxLineLength));
		}
	}

	if (buffer.compare(""))
	{
		lines.push_back(buffer);
	}

	words.clear();

	for each (string curString in lines)
	{
		printf("%s\n", curString.c_str());
	}
}
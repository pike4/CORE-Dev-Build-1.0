#include "StaticTextElement.h"
#include "CORE_Graphics.h"
#include "CORE_Resources.h"

StaticTextElement::StaticTextElement(int aX, int aY, int aW, int aH, RenderableCharSet* charSet)
	:VisibleElement(aX, aY, aW, aH)
{
	this->charSet = charSet;

	maxLineLength = w / charSet->fontWidth('W');
	maxLines = h / charSet->fontHeight;

	lineIndex = 0;
}

StaticTextElement::StaticTextElement(int aX, int aY, int aW, int aH, RenderableCharSet* charSet, std::string text)
	:StaticTextElement(aX, aY, aW, aH, charSet)
{
	this->charSet = charSet;
	this->text = text;

	maxLineLength = w / charSet->fontWidth('W');
	maxLines = h / charSet->fontHeight;

	lineIndex = 0;
}

StaticTextElement::StaticTextElement()
	:VisibleElement()
{
}

StaticTextElement::StaticTextElement(StaticTextElement& copy)
	:VisibleElement(copy)
{
	
}

void StaticTextElement::draw()
{
	int penX = *x;
	int penY = *y;

	for (unsigned int i = lineIndex; i < lines.size() && i < maxLines; i++)
	{
		for (unsigned int j = 0; j < lines[i].length(); j++)
		{
			char curChar = lines[i][j];
			CORE_Graphics::addDraw(penX, penY, (*charSet)[curChar], *zIndex);
			penX += charSet->fontWidth(curChar);
		}

		penY += charSet->fontHeight;
		penX = *x;
	}
}

void StaticTextElement::stringToLines(std::string message)
{
	unsigned int length = message.length();
	std::vector<std::string> words;

	std::string buffer = "";

	//Convert given char* to vector of char* words
	for (unsigned int x = 0; x < length; x++)
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
	for (unsigned int x = 0; x < words.size(); x++)
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

void StaticTextElement::getText(XMLNode definer)
{
	text = definer.getVariable("text");
	std::string charSetName = definer.getVariable("characterSet");

	if (!charSetName.empty())
	{
		charSet = CORE_Resources::assignCharSet(charSetName);
	}

	else
	{
		//TODO: Log error
		charSet = NULL;
	}
}

VisibleElement* StaticTextElement::spawnCopy()
{
	return new StaticTextElement(*this);
}
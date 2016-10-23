#include "StaticTextElement.h"
#include "VideoManager.h"
#include "SystemManager.h"

StaticTextElement::StaticTextElement(int aX, int aY, int aW, int aH, RenderableCharSet* charSet)
	:VisibleElement(aX, aY, aW, aH)
{
	this->charSet = charSet;

	maxLineLength = w / charSet->fontWidth;
	maxLines = h / charSet->fontHeight;

	lineIndex = 0;
}

StaticTextElement::StaticTextElement(int aX, int aY, int aW, int aH, RenderableCharSet* charSet, std::string text)
	:StaticTextElement(aX, aY, aW, aH, charSet)
{
	this->charSet = charSet;
	this->text = text;

	maxLineLength = w / charSet->fontWidth;
	maxLines = h / charSet->fontHeight;

	lineIndex = 0;
}

StaticTextElement::StaticTextElement(pugi::xml_node node)
	:VisibleElement(node)
{
	getArgsFromNode(node);
}

StaticTextElement::StaticTextElement(StaticTextElement& copy)
	:VisibleElement(copy)
{
	
}

void StaticTextElement::draw()
{
	int penX = *x;
	int penY = *y;

	for (int i = lineIndex; i < lines.size() && i < maxLines; x++)
	{
		for (int j = 0; j < lines[i].length(); j++)
		{
			VideoManager::applyTexture(penX, penY, charSet->charSet[lines[i][j]]);
			penX += charSet->fontWidth;
		}

		penY += charSet->fontHeight;
		penX = *x;
	}
}

void StaticTextElement::stringToLines(std::string message)
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

void StaticTextElement::getArgsFromNode(pugi::xml_node node)
{
	text = node.child("text").first_child().value();
	std::string charSetName = node.child("CharacterSet").first_child().value();

	if (!charSetName.empty())
	{
		charSet = SystemManager::assignCharSet(charSetName);
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
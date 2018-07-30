#pragma once
#include <vector>
#include <string>
#include "pugixml.hpp"

namespace Util
{
	std::vector<std::string> tokenize(std::string src, char delim);

	std::string toLower(char* str);
	std::string toLower(const pugi::char_t* str);

	int toInt(std::string str);
	float toFloat(std::string str);
	double toDouble(std::string str);
}
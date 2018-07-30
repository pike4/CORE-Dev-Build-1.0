#pragma once
#include <vector>
#include <string>
#include "pugixml.hpp"

namespace Util
{
	std::vector<std::string> tokenize(std::string src, char delim);

	std::string toLower(std::string);
	std::string toLower(char* str);
	std::string toLower(const pugi::char_t* str);

	// Convert from string
	int toInt(std::string str);
	float toFloat(std::string str);
	double toDouble(std::string str);
	bool toBool(std::string str);

	bool isIntegral(std::string str);
	bool isDecimal(std::string str);
	bool isBool(std::string str);
}
#pragma once
#include <vector>
#include <string>
#include "pugixml.hpp"

namespace CORE_Util
{
	std::vector<std::string> tokenize(std::string src, char delim);

	std::string toLower(char* str);
	std::string toLower(const pugi::char_t* str);
}
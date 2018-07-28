#include "CORE_Util.h"

namespace CORE_Util
{
	std::vector<std::string> tokenize(std::string src, char delim)
	{
		std::string cur = "";

		std::vector<std::string> ret;

		for (int i = 0; i < src.length(); i++)
		{
			if (src[i] == delim || src[i] == ' ')
			{
				ret.push_back(cur);
				cur = "";
			}

			else
			{
				cur += src.substr(i, 1);
			}
		}

		if (cur != "")
		{
			ret.push_back(cur);
		}

		return ret;
	}

	std::string toLower(char* str)
	{
		int i = 0;
		std::string ret;

		while (str[i] != '\0')
		{
			ret.append(1, tolower(str[i++]));
		}

		return ret;
	}

	std::string toLower(const pugi::char_t* str)
	{
		return toLower((char*)str);
	}
}
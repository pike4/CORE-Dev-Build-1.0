#include "CORE_Util.h"

#include <cctype>

namespace Util
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

	// Converts a string to int. Return 0 if string
	// contains non-digits
	int toInt(std::string str)
	{
		if (str.empty())
			return 0;

		for (int i = 0; i < str.length(); i++)
		{
			if (!isdigit(str[i]))
			{
				return 0;
			}
		}

		return stoi(str);
	}

	// Converts a string to float. Return 0 if string
	// contains non-digits or more than one decimal point
	float toFloat(std::string str)
	{
		if (str.empty())
			return 0;

		bool hasDot = false;

		for (int i = 0; i < str.length(); i++)
		{
			if (!isdigit(str[i]) || (str[i] == '.' && hasDot))
			{
				return 0;
			}

			if (str[i] == '.')
			{
				hasDot = true;
			}
		}

		return stof(str);
	}

	// Converts a string to double. Return 0 if string
	// contains non-digits or more than one decimal point
	double toDouble(std::string str)
	{
		if (str.empty())
			return 0;

		bool hasDot = false;

		for (int i = 0; i < str.length(); i++)
		{
			if (!isdigit(str[i]) || (str[i] == '.' && hasDot))
			{
				return 0;
			}

			if (str[i] == '.')
			{
				hasDot = true;
			}
		}

		return stod(str);
	}
}
#include "CORE_Utilities.h"

namespace CORE_Utilities
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
}
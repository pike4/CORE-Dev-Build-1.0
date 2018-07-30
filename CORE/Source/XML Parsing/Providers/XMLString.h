#pragma once
#include <string>



class XMLString
{
public:
	XMLString();
	operator std::string();
	operator const char*();
	XMLString(const char* other);
	XMLString(std::string other);

	std::string operator=(XMLString);
	void operator=(const char* other);
	void operator=(std::string);
	std::string operator*();
	bool operator==(std::string other);

protected:
	std::string value;
};
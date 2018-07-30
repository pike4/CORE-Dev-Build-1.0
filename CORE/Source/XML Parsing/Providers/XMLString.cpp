#include "XMLString.h"
#include "CORE_Factory.h"
#include "CORE_Util.h"

XMLString::XMLString()
{
	value = "";
}

std::string XMLString::operator=(XMLString other )
{
	return other.value;
}

XMLString::operator const char*()
{
	return value.c_str();
}

XMLString::operator std::string()
{
	return value;
}

XMLString::XMLString(const char* other)
{
	value = other;
}

XMLString::XMLString(std::string other)
{
	value = other;
}

void XMLString::operator=(const char* other)
{
	value = other;
}

void XMLString::operator=(std::string other)
{
	value = other;
}
std::string XMLString::operator*()
{
	return value;
}

bool XMLString::operator==(std::string other)
{
	if (Util::toLower(value) == Util::toLower(other))
		return true;

	if (CORE_Factory::getAlias(other) != "")
		return true;

	return false;
}
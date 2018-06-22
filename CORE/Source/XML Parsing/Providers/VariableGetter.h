#pragma once
#include "Provider.h"


class VariableGetter : public Provider
{
	virtual std::string getValue(pugi::xml_node node);
};
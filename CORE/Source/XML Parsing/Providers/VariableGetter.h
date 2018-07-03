#pragma once
#include "Provider.h"
#include "TemplateDef.h"


class VariableGetter : public Provider
{
public:
    VariableGetter(StringAddress add);
    virtual std::string getValue(pugi::xml_node node);
private:
    StringAddress address;
};
#include "VariableGetter.h"
#include "CORE_Util.h"

std::string VariableGetter::getValue(pugi::xml_node node)
{
    std::string ret = "";
    std::string toSearch = node.child(address.varName.c_str()).first_child().value();

    std::vector<std::string> vars = Util::tokenize(toSearch, ',');

    if (address.index < vars.size())
    {
        ret = vars[address.index];
    }

    return ret;
}

VariableGetter::VariableGetter(StringAddress add)
{
    address = add;
}

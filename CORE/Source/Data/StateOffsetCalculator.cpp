#include "StateOffsetCalculator.h"
#include "CORE_SystemIO.h"

#include <algorithm>
#include <functional>

StateOffsetCalculator::StateOffsetCalculator(std::vector<std::string> newVars)
{
    //Vector must be even: these are name-size pairs
    if (newVars.size() % 2)
        return;

    std::vector<std::string>  names;
    int runningSize = 0;
    int temp = 0;

    //Extract the names to a new vector for sorting 
    //and temporarily store the sizes in the offsets map
    for (unsigned int i = 0; i < newVars.size(); i += 2)
    {
        int newSize = CORE_TypeTraits::getDataObjectSize(newVars[i + 1]);
        if (newSize == 0)
            CORE_SystemIO::error("Undefined type in offset calculator constructor");

        offsets[newVars[i]] = newSize;

        names.push_back(newVars[i]);
    }

    //Lexographically sort the names
    std::sort(names.begin(), names.end(), std::less<std::string>());

    //Convert the sizes in the map to their relative offsets
    //based on lexographical order of the keys
    for (unsigned int i = 0; i < names.size(); i++)
    {
        temp = offsets[names[i]];

        offsets[names[i]] = runningSize;
        runningSize += temp;
    }
}

int StateOffsetCalculator::getOffset(std::string variableName)
{
    int ret = -1;

    if (offsets.find(variableName) != offsets.end())
    {
        ret = offsets[variableName];
    }

    return ret;
}

std::vector<std::string> StateOffsetCalculator::getFingerprint()
{
    std::vector<std::string> ret;

    for (std::map<std::string, int>::iterator it = offsets.begin(); it != offsets.end(); ++it)
    {
        ret.push_back(it->first);
        ret.push_back(std::to_string(it->second));
    }

    return ret;
}
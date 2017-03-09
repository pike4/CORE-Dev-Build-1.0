#pragma once
#include "Data.h"
#include <map>
#include <string>
#include <vector>

class StateOffsetCalculator
{
public:
    //Parse the given vector of the form: {name1, type1, name2, type2...}
    //and assign offsets for accessing them based on their lexographical order
    StateOffsetCalculator(std::vector<std::string> newVars);

    //Return pointer offset for variable of the given name
    int getOffset(std::string variableName);

    //Return a vector containing name-size pairs for all variables this covers
    std::vector<std::string> getFingerprint();

private:
    std::map<std::string, int> offsets;

    int totalSize;
};
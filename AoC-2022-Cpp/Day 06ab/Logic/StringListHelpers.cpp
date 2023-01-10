#include <iostream>
#include "StringListHelpers.h"

std::string StringListHelpers::GetListEntryAt(std::list<std::string> inputList, int index)
{
    auto it = inputList.begin();

    for(int i = 0; i < index; i++)
        ++it;

    return *it;
}

std::list<std::string> StringListHelpers::ReplaceEntryAt(std::list<std::string> inputList, int index, std::string replacementEntry)
{
    // Remove old line
    auto itForRemove = inputList.begin();

    for(int i = 0; i < index; i++)
        ++itForRemove;

    inputList.erase(itForRemove);

    // Replace with new line
    auto it = inputList.begin();

    for(int i = 0; i < index; i++)
        ++it;

    inputList.insert(it, replacementEntry);

    return inputList;
}
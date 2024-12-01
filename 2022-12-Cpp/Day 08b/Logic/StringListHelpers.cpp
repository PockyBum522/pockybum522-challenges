#include <iostream>
#include "StringListHelpers.h"

string StringListHelpers::GetListEntryAt(list<string>& inputList, int index)
{
    auto it = inputList.begin();

    for(int i = 0; i < index; i++)
        ++it;

    return *it;
}

list<string> StringListHelpers::ReplaceEntryAt(list<string> inputList, int index, string replacementEntry)
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
#include "CharListHelpers.h"

char CharListHelpers::GetListEntryAt(std::list<char> inputList, int index)
{
    std::list<char>::iterator it = inputList.begin();

    for(int i = 0; i < index; i++)
        ++it;

    return *it;
}
#include "CharListHelpers.h"

char CharListHelpers::GetListEntryAt(list<char> inputList, int index)
{
    list<char>::iterator it = inputList.begin();

    for(int i = 0; i < index; i++)
        ++it;

    return *it;
}
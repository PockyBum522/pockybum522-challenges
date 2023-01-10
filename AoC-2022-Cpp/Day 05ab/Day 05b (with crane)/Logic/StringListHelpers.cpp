#include <iostream>
#include "StringListHelpers.h"
#include "ConsoleHelpers.h"

ConsoleHelpers _consoleHelpers;

void StringListHelpers::PrintList(std::list<std::string> listToPrint)
{
    int lineWidth = GetListEntryAt(listToPrint, 1).size();

    for (int y = 0; y < listToPrint.size(); y++)
    {
        std::string currentLine = GetListEntryAt(listToPrint, y);

        for (int x = 0; x < lineWidth; x++)
        {
            _consoleHelpers.DrawCharacterAt(currentLine[x], x, y);
        }
    }
}

std::string StringListHelpers::GetListEntryAt(std::list<std::string> inputList, int index)
{
    std::list<std::string>::iterator it = inputList.begin();

    for(int i = 0; i < index; i++)
        ++it;

    return *it;
}

std::list<std::string> StringListHelpers::ReplaceEntryAt(std::list<std::string> inputList, int index, std::string replacementEntry)
{
    // Remove old line
    std::list<std::string>::iterator itForRemove = inputList.begin();

    for(int i = 0; i < index; i++)
        ++itForRemove;

    inputList.erase(itForRemove);

    // Replace with new line
    std::list<std::string>::iterator it = inputList.begin();

    for(int i = 0; i < index; i++)
        ++it;

    inputList.insert(it, replacementEntry);

    return inputList;
}
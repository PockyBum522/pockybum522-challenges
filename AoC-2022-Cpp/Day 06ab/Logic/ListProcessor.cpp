#include <iostream>
#include "ListProcessor.h"
#include "StringListHelpers.h"
#include "CharListHelpers.h"

using namespace std;

void ListProcessor::ProcessList(list<string> inputList)
{
    string firstLine = StringListHelpers::GetListEntryAt(inputList, 0);

    for (int i = 0; i < firstLine.size(); i++)
    {
        string lettersToCheck = getPreviousXLetters(firstLine, i, 4);

        if (lettersToCheck.size() > 0 &&
            allLettersAreUnique(lettersToCheck))
        {
            cout << "Found unique letters at position #: " << i << endl;

            return;
        }
    }
}

bool ListProcessor::allLettersAreUnique(std::string lettersToCheck)
{
    for (int i = 0; i < lettersToCheck.size(); i++)
    {
        for (int j = 0; j < lettersToCheck.size(); j++)
        {
            if (j == i) continue;

            if (lettersToCheck[i] == lettersToCheck[j])
                return false;
        }
    }

    return true;
}

string ListProcessor::getPreviousXLetters(std::string inputString, int startPosition, int howManyToGet)
{
    if (startPosition < howManyToGet)
        return "";

    string returnLetters;

    for (int i = startPosition - howManyToGet; i < startPosition; i++)
    {
        returnLetters += inputString[i];
    }

    return returnLetters;
}

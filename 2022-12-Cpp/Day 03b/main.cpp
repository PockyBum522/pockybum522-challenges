#include <iostream>
#include <sstream>
#include <list>
#include "RawData/RawData.h"
using namespace std;

string getListEntryAt(int index);

char findSharedLetter(string firstString, string secondString, string thirdString);

bool isCharInString(char needle, string haystack);

int getLetterValue(char letter);

void processList();

list<string> allLines;
int total = 0;

int main()
{
    string line;
    istringstream f(RawData::INPUT_DATA_RAW);

    while (getline(f, line))
    {
        allLines.push_back(line);
    }

    processList();

    return 0;
}

void processList()
{
    for (int i = 0; i < allLines.size(); i += 3)
    {
        string firstElf = getListEntryAt(i);
        string secondElf = getListEntryAt(i + 1);
        string thirdElf = getListEntryAt(i + 2);

        cout << "First Elf Position: " << i << " and contents: " << firstElf << endl;
        cout << "Second Elf Position: " << i + 1 << " and contents: " << secondElf << endl;
        cout << "Third Elf Position: " << i + 2 << " and contents: " << thirdElf << endl;

        char sharedBetweenAllThree = findSharedLetter(firstElf, secondElf, thirdElf);
        int letterValue = getLetterValue(sharedBetweenAllThree);

        cout << "Letter shared between all three: " << sharedBetweenAllThree << " and value: " << letterValue << endl;

        total += letterValue;

        cout << "Running total: " << total << endl << endl;
    }
}

string getListEntryAt(int index)
{
    list<string>::iterator it = allLines.begin();

    for(int i = 0; i < index; i++)
        ++it;

    return *it;
}

int getLetterValue(char letter)
{
    if (islower(letter))
        return int(letter) - 96;

    if (isupper(letter))
        return int(letter) - 38;

    return 0;
}

char findSharedLetter(string firstString, string secondString, string thirdString)
{
    for (int i = 0; i < firstString.length(); i++)
    {
        char needle = firstString[i];

        if (!isCharInString(needle, secondString)) continue;

        if (isCharInString(needle, thirdString))
            return needle;
    }

    return '!';
}

bool isCharInString(char needle, string haystack)
{
    for (int i = 0; i < haystack.length(); i++)
    {
        if (needle != haystack[i]) continue;

        return true;
    }

    return false;
}

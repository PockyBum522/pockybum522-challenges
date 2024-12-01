#include <iostream>
#include <sstream>
#include <list>
#include "RawData/RawData.h"
using namespace std;

string getListEntryAt(int index);

void processList();

bool isRangePartiallyContainedInOtherRange(string rangeOne, string rangeTwo);

bool isNumberInRange(int needle, int rangeMin, int rangeMax);

string getFirstHalfSplitAt(string fullLine, char needle);
string getLastHalfSplitAt(string fullLine, char needle);

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
    for (int i = 0; i < allLines.size(); i ++)
    {
        string fullLine = getListEntryAt(i);

        string firstElfRangeRaw = getFirstHalfSplitAt(fullLine, ',');
        string secondElfRangeRaw = getLastHalfSplitAt(fullLine, ',');

        cout << "#" << i << " - Full line: " << fullLine << endl;
        cout << "#" << i << " - First Elf: " << firstElfRangeRaw << endl;
        cout << "#" << i << " - Second Elf: " << secondElfRangeRaw << endl;

        if (isRangePartiallyContainedInOtherRange(firstElfRangeRaw, secondElfRangeRaw))
        {
            cout << "One was contained partially in the other" << endl;
            total ++;
        }

        cout << "Running total: " << total << endl << endl;
    }
}

string getFirstHalfSplitAt(string fullLine, char needle)
{
    int needlePosition = fullLine.find(needle);

    return fullLine.substr(0, needlePosition);
}

string getLastHalfSplitAt(string fullLine, char needle)
{
    int needlePosition = fullLine.find(needle);

    int fullLineLength = fullLine.length();

    return fullLine.substr(needlePosition + 1, fullLineLength - needlePosition - 1);
}

bool isRangePartiallyContainedInOtherRange(string rangeOne, string rangeTwo)
{
    string firstElfRangeStartString = getFirstHalfSplitAt(rangeOne, '-');
    string firstElfRangeEndString = getLastHalfSplitAt(rangeOne, '-');
    string secondElfRangeStartString = getFirstHalfSplitAt(rangeTwo, '-');
    string secondElfRangeEndString = getLastHalfSplitAt(rangeTwo, '-');

    int firstElfRangeStart = stoi(firstElfRangeStartString);
    int firstElfRangeEnd = stoi(firstElfRangeEndString);
    int secondElfRangeStart = stoi(secondElfRangeStartString);
    int secondElfRangeEnd = stoi(secondElfRangeEndString);

//    cout << "FirstElfRangeStart: " << firstElfRangeStart << endl;
//    cout << "firstElfRangeEnd: " << firstElfRangeEnd << endl;
//    cout << "secondElfRangeStart: " << secondElfRangeStart << endl;
//    cout << "secondElfRangeEnd: " << secondElfRangeEnd << endl;

    if (isNumberInRange(firstElfRangeStart, secondElfRangeStart, secondElfRangeEnd))
        return true;

    if (isNumberInRange(firstElfRangeEnd, secondElfRangeStart, secondElfRangeEnd))
        return true;

    if (isNumberInRange(secondElfRangeStart, firstElfRangeStart, firstElfRangeEnd))
        return true;

    if (isNumberInRange(secondElfRangeEnd, firstElfRangeStart, firstElfRangeEnd))
        return true;

    return false;
}

bool isNumberInRange(int needle, int rangeMin, int rangeMax)
{
    return needle >= rangeMin && needle <= rangeMax;
}

string getListEntryAt(int index)
{
    list<string>::iterator it = allLines.begin();

    for(int i = 0; i < index; i++)
        ++it;

    return *it;
}
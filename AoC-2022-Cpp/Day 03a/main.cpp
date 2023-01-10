#include <iostream>
#include <sstream>
#include <list>
#include "RawData/RawData.h"

using namespace std;

void processLine(string line);

string getFirstHalfOf(string line);
string getLastHalfOf(string line);

char findSharedLetter(string firstHalf, string lastHalf);

bool isCharInString(char needle, string haystack);

int getLetterValue(char letter);

int total = 0;

int main()
{
    string line;
    istringstream f(RawData::INPUT_DATA_RAW);

    while (getline(f, line))
    {
        processLine(line);
    }

    return 0;
}

void processLine(string line)
{
    string firstHalf = getFirstHalfOf(line);
    string lastHalf = getLastHalfOf(line);

    char sharedLetter = findSharedLetter(firstHalf, lastHalf);

    int letterValue = getLetterValue(sharedLetter);

    total += letterValue;

//    cout << "line: " << line << endl;
//    cout << "firstH: " << firstHalf << endl;
//    cout << "lastH: " << lastHalf << endl;
//    cout << "Shared character was: " << sharedLetter << endl ;
//    cout << "Letter value is: " << letterValue << endl << endl ;

    cout << "Running total is: " << total << endl;
}

int getLetterValue(char letter)
{
    if (islower(letter))
        return int(letter) - 96;

    if (isupper(letter))
        return int(letter) - 38;

    return 0;
}

char findSharedLetter(string firstHalf, string lastHalf)
{
    for (int i = 0; i < firstHalf.length(); i++)
    {
        if (isCharInString(firstHalf[i], lastHalf))
            return firstHalf[i];
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

string getFirstHalfOf(string line)
{
    int halfLineLength = line.length() / 2;

    string firstHalfString = "";

    for (int i = 0; i < halfLineLength; i++)
    {
        firstHalfString += line[i];
    }

    return firstHalfString;
}

string getLastHalfOf(string line)
{
    int halfLineLength = line.length() / 2;

    string lastHalfString = "";

    for (int i = halfLineLength; i < line.length(); i++)
    {
        lastHalfString += line[i];
    }

    return lastHalfString;
}

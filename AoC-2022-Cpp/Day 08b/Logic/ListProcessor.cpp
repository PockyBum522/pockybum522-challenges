#include <iostream>
#include "ListProcessor.h"
#include "StringListHelpers.h"
#include "CharListHelpers.h"

using namespace std;

bool ConsoleWriteMessagesEnabled = false;

void ListProcessor::ConsoleWriteLine(string&& message, int newLinesFollowing, bool forceWrite)
{
    if (!ConsoleWriteMessagesEnabled && !forceWrite)
        return;

    cout << message;

    for (int i = 0; i < newLinesFollowing; i++)
        cout << endl;
}

void ListProcessor::ProcessList(list<string>& inputList)
{
    int highestScore = 0;

    int columns = (int)StringListHelpers::GetListEntryAt(inputList, 0).size();

    int rows = (int)inputList.size();

    for (int x = 0; x < columns; x++)
    {
        for (int y = 0; y < rows; y++)
        {
            int currentScore = calculateTreeScoreAt(x, y, inputList);

            if (currentScore > highestScore)
                highestScore = currentScore;
        }
    }

    ConsoleWriteLine("Highest score: " + to_string(highestScore), 2, true);
}

int ListProcessor::calculateTreeScoreAt(int x, int y, list<string> inputList)
{
    ConsoleWriteLine("Checking tree at X: " + to_string(x) + ", Y: " + to_string(y) + " which is: " + to_string(GetTreeIntAt(x, y, inputList)));

    string currentRow = StringListHelpers::GetListEntryAt(inputList, y);

    int scoreToLeft = calculateScoreToLeftOf(x, y, currentRow);
    int scoreToRight = calculateScoreToRightOf(x, y, currentRow);

    int scoreToNorth = calculateScoreToNorthOf(x, y, inputList);
    int scoreToSouth = calculateScoreToSouthOf(x, y, inputList);

    int currentScore = scoreToLeft * scoreToRight * scoreToNorth * scoreToSouth;

    ConsoleWriteLine("Score: " + to_string(currentScore), 2);

    return currentScore;
}

int ListProcessor::calculateScoreToLeftOf(int x, int y, string& currentRow)
{
    if (x == 0) return 0;

    string currentTree;
    currentTree += currentRow[x];

    int currentTreeNumber = stoi(currentTree);

    int currentScore = 0;

    for (int i = x - 1; i >= 0; i--)
    {
        string numberToCompareTo;
        numberToCompareTo += currentRow[i];

        int numberToCompareToInt = stoi(numberToCompareTo);

        ConsoleWriteLine("Checking to left. i is:" + to_string(i) + " Comparing: " + to_string(currentTreeNumber) + " to: " + to_string(numberToCompareToInt));

        if (numberToCompareToInt >= currentTreeNumber)
        {
            ConsoleWriteLine("Taller or equal tree found to the left!");
            ConsoleWriteLine("Left score: " + to_string(currentScore));

            return currentScore;
        }

        currentScore++;
    }

    ConsoleWriteLine("Left score: " + to_string(currentScore));
    return currentScore;
}

int ListProcessor::calculateScoreToRightOf(int x, int y, string& currentRow)
{
    if (x == currentRow.size()) return 0;

    string currentTree;
    currentTree += currentRow[x];

    int currentTreeNumber = stoi(currentTree);

    int currentScore = 0;

    for (int i = x + 1; i < currentRow.size(); i++)
    {
        string numberToCompareTo;
        numberToCompareTo += currentRow[i];

        int numberToCompareToInt = stoi(numberToCompareTo);

        ConsoleWriteLine("Checking to right. i is:" + to_string(i) + " Comparing: " + to_string(currentTreeNumber) + " to: " + to_string(numberToCompareToInt));

        currentScore++;

        if (numberToCompareToInt >= currentTreeNumber)
        {
            ConsoleWriteLine("Taller or equal tree found to the right!");
            ConsoleWriteLine("right score: " + to_string(currentScore));

            return currentScore;
        }
    }

    ConsoleWriteLine("right score: " + to_string(currentScore));
    return currentScore;
}

int ListProcessor::calculateScoreToNorthOf(int x, int y, list<string>& inputList)
{
    if (y == 0) return 0;

    string currentColumn;

    for (int i = 0; i < inputList.size(); i++)
    {
        currentColumn += StringListHelpers::GetListEntryAt(inputList, i)[x];
    }

    ConsoleWriteLine("Current column #" + to_string(x) + ": " + currentColumn);

    string currentRow = StringListHelpers::GetListEntryAt(inputList, y);

    string currentTree;
    currentTree += currentRow[x];

    int currentTreeNumber = stoi(currentTree);

    int currentScore = 0;

    for (int i = y - 1; i >= 0; i--)
    {
        string numberToCompareTo;
        numberToCompareTo += currentColumn[i];

        int numberToCompareToInt = stoi(numberToCompareTo);

        ConsoleWriteLine("Checking to north. i is:" + to_string(i) + " Comparing: " + to_string(currentTreeNumber) + " to: " + to_string(numberToCompareToInt));

        currentScore++;

        if (numberToCompareToInt >= currentTreeNumber)
        {
            ConsoleWriteLine("Taller tree found to the north!");
            ConsoleWriteLine("North score: " + to_string(currentScore));

            return currentScore;
        }
    }

    ConsoleWriteLine("North score: " + to_string(currentScore));
    return currentScore;
}

int ListProcessor::calculateScoreToSouthOf(int x, int y, list<string>& inputList)
{
    string currentColumn;

    for (int i = 0; i < inputList.size(); i++)
    {
        currentColumn += StringListHelpers::GetListEntryAt(inputList, i)[x];
    }

    if (y == currentColumn.size()) return 0;

    //ConsoleWriteLine("Current column #" + x + ": " + currentColumn);

    string currentRow = StringListHelpers::GetListEntryAt(inputList, y);

    string currentTree;
    currentTree += currentRow[x];

    int currentTreeNumber = stoi(currentTree);

    int currentScore = 0;

    for (int i = y + 1; i < currentColumn.size(); i++)
    {
        string numberToCompareTo;
        numberToCompareTo += currentColumn[i];

        int numberToCompareToInt = stoi(numberToCompareTo);

        ConsoleWriteLine("Checking to south. i is:" + to_string(i) + " Comparing: " + to_string(currentTreeNumber) + " to: " + to_string(numberToCompareToInt));

        currentScore++;

        if (numberToCompareToInt >= currentTreeNumber)
        {
            ConsoleWriteLine("Taller tree found to the south!");
            ConsoleWriteLine("South score: " + to_string(currentScore));

            return currentScore;
        }
    }

    ConsoleWriteLine("South score: " + to_string(currentScore));
    return currentScore;
}

long ListProcessor::GetTreeIntAt(int x, int y, list<string> inputList)
{
    string currentTreeRow = StringListHelpers::GetListEntryAt(inputList, y);
    //ConsoleWriteLine("CurrentTreeRow: " + currentTreeRow);

    string currentTreeChar;
    currentTreeChar += currentTreeRow[x];
    //ConsoleWriteLine("CurrentTreeChar: " + currentTreeChar);

    return stoi(currentTreeChar);
}



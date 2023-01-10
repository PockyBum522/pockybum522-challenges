#include <iostream>
#include "ListProcessor.h"
#include "StringListHelpers.h"
#include "CharListHelpers.h"

using namespace std;

void ListProcessor::ConsoleWriteLine(string&& message, int newLinesFollowing)
{
    cout << message;

    for (int i = 0; i < newLinesFollowing; i++)
        cout << endl;
}

void ListProcessor::ProcessList(list<string>& inputList)
{
    int totalVisibleTrees = 0;

    int columns = (int)StringListHelpers::GetListEntryAt(inputList, 0).size();

    int rows = (int)inputList.size();

    for (int x = 0; x < columns; x++)
    {
        for (int y = 0; y < rows; y++)
        {
            if (treeIsVisibleAt(x, y, inputList))
                totalVisibleTrees++;
        }
    }

    ConsoleWriteLine("Total visible trees: " + to_string(totalVisibleTrees), 2);
}

bool ListProcessor::treeIsVisibleAt(int x, int y, list<string> inputList)
{
    ConsoleWriteLine("Checking tree at X: " + to_string(x) + ", Y: " + to_string(y) + " which is: " + to_string(GetTreeIntAt(x, y, inputList)), 2);

    int columns = (int)StringListHelpers::GetListEntryAt(inputList, 0).size();

    int rows = (int)inputList.size();

    // Handle outside trees
    if (x == 0 || x == columns) return true;
    if (y == 0 || y == rows) return true;

    ConsoleWriteLine("Tree was NOT visible just because it was on the outside");

    string currentRow = StringListHelpers::GetListEntryAt(inputList, y);

    // Handle inside trees
    if (treeVisibleBecauseOfTreesInRow(x, y, currentRow)) return true;
    ConsoleWriteLine("Tree was NOT visible just because of other trees in its row");

    if (treeVisibleBecauseOfTreesInColumn(x, y, inputList)) return true;
    ConsoleWriteLine("Tree was NOT visible just because of other trees in its column");

    ConsoleWriteLine("Tree was NOT visible, period");
    return false;
}

bool ListProcessor::treeVisibleBecauseOfTreesInRow(int x, int y, string& currentRow)
{
    if (treeVisibleBecauseOfTreesToItsLeft(x, y, currentRow)) return true;
    if (treeVisibleBecauseOfTreesToItsRight(x, y, currentRow)) return true;

    return false;
}

bool ListProcessor::treeVisibleBecauseOfTreesInColumn(int x, int y, list<string>& inputList)
{
    if (treeVisibleBecauseOfTreesToItsNorth(x, y, inputList)) return true;
    if (treeVisibleBecauseOfTreesToItsSouth(x, y, inputList)) return true;

    return false;
}

bool ListProcessor::treeVisibleBecauseOfTreesToItsLeft(int x, int y, string& currentRow)
{
    string currentTree;
    currentTree += currentRow[x];

    int currentTreeNumber = stoi(currentTree);

    for (int i = x - 1; i >= 0; i--)
    {
        string numberToCompareTo;
        numberToCompareTo += currentRow[i];

        int numberToCompareToInt = stoi(numberToCompareTo);

        ConsoleWriteLine("Checking to left. i is:" + to_string(i) + " Comparing: " + to_string(currentTreeNumber) + " to: " + to_string(numberToCompareToInt));

        if (numberToCompareToInt >= currentTreeNumber)
        {
            ConsoleWriteLine("Taller tree found to the left!");
            return false;
        }
    }

    return true;
}

bool ListProcessor::treeVisibleBecauseOfTreesToItsRight(int x, int y, string& currentRow)
{
    string currentTree;
    currentTree = currentRow[x];

    int currentTreeNumber = stoi(currentTree);

    for (int i = x + 1; i < currentRow.size(); i++)
    {
        string numberToCompareTo;
        numberToCompareTo += currentRow[i];

        int numberToCompareToInt = stoi(numberToCompareTo);

        ConsoleWriteLine("Checking to right. i is:" + to_string(i) + " Comparing: " + to_string(currentTreeNumber) + " to: " + to_string(numberToCompareToInt));

        if (numberToCompareToInt >= currentTreeNumber)
        {
            ConsoleWriteLine("Taller tree found to the right!");
            return false;
        }
    }

    return true;
}

bool ListProcessor::treeVisibleBecauseOfTreesToItsNorth(int x, int y, list<string>& inputList)
{
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

    for (int i = y - 1; i >= 0; i--)
    {
        string numberToCompareTo;
        numberToCompareTo += currentColumn[i];

        int numberToCompareToInt = stoi(numberToCompareTo);

        ConsoleWriteLine("Checking to north. i is:" + to_string(i) + " Comparing: " + to_string(currentTreeNumber) + " to: " + to_string(numberToCompareToInt));

        if (numberToCompareToInt >= currentTreeNumber)
        {
            ConsoleWriteLine("Taller tree found to the north!");
            return false;
        }
    }

    return true;
}

bool ListProcessor::treeVisibleBecauseOfTreesToItsSouth(int x, int y, list<string>& inputList)
{
    string currentColumn;

    for (int i = 0; i < inputList.size(); i++)
    {
        currentColumn += StringListHelpers::GetListEntryAt(inputList, i)[x];
    }

    //ConsoleWriteLine("Current column #" + x + ": " + currentColumn);

    string currentRow = StringListHelpers::GetListEntryAt(inputList, y);

    string currentTree;
    currentTree += currentRow[x];

    int currentTreeNumber = stoi(currentTree);

    for (int i = y + 1; i < currentColumn.size(); i++)
    {
        string numberToCompareTo;
        numberToCompareTo += currentColumn[i];

        int numberToCompareToInt = stoi(numberToCompareTo);

        ConsoleWriteLine("Checking to south. i is:" + to_string(i) + " Comparing: " + to_string(currentTreeNumber) + " to: " + to_string(numberToCompareToInt));

        if (numberToCompareToInt >= currentTreeNumber)
        {
            ConsoleWriteLine("Taller tree found to the south!");
            return false;
        }
    }

    return true;
}

long ListProcessor::GetTreeIntAt(int x, int y, list<string> inputList)
{
    string currentTreeRow = StringListHelpers::GetListEntryAt(inputList, y);
    //ConsoleWriteLine("CurrentTreeRow: " + currentTreeRow);

    string currentTreeChar;
    currentTreeChar += currentTreeRow[x];
    ConsoleWriteLine("CurrentTreeChar: " + currentTreeChar);

    return stoi(currentTreeChar);
}



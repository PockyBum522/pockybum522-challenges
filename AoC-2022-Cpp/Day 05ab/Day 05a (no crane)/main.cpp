#include <iostream>
#include <sstream>
#include <list>
#include <unistd.h>
#include "RawData/RawData.h"
#include "Models/MoveInstruction.h"

using namespace std;

string getListEntryAt(list<string> inputList, int index);
list<string> replaceEntryAt(list<string> inputList, int index, string replacementEntry);

void processList();

list<string> getAsciiCratesPartOfData();
list<string> getInstructionsPartOfData();

void printList(list<string> list1);

MoveInstruction parseMoveInstruction(string instructionLine);

void executeMove(MoveInstruction instruction, string currentInstructionText, string nextInstructionText);

int getLowestFreePositionInColumn(int column);
int getTopBoxYPositionInColumn(int column);
char getTopBoxLetterInColumn(int column);
void eraseBoxAt(int column, int yPosition);
void createBoxAt(int column, int yPosition, char letterOnBox);

int calculateColumnXPosition(int column);

char intToChar(int input);

void DisplayCratesAndSleep(string currentInstructionText, string nextInstructionText);

list<string> cratesAscii;
list<string> allLines;

int blankLinesOnTop = 35;
int sleepTimeMicroseconds = 50000;
//int sleepTimeMicroseconds = 100000;

int main()
{
    system("cls");

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
    cratesAscii = getAsciiCratesPartOfData();
    list<string> instructionsRaw = getInstructionsPartOfData();

    instructionsRaw.push_front(""); // Padding because we're showing current and next instructions each round

    int i = 0;

    do
    {
        string currentInstructionText = getListEntryAt(instructionsRaw, i);

        MoveInstruction currentMove = parseMoveInstruction(currentInstructionText);

        // All rounds other than the second to last and last rounds
        if (i < instructionsRaw.size() - 1)
        {
            string nextInstructionText = getListEntryAt(instructionsRaw, i + 1);

            executeMove(currentMove, currentInstructionText, nextInstructionText);

            system("cls");

            continue;
        }

        // For the second to last round, say done instead
        if (i == instructionsRaw.size() - 1)
        {
            executeMove(currentMove, currentInstructionText, "DONE!");

            system("cls");
        }
    }
    while (++i < instructionsRaw.size());

    // For the last round, say done on both
    DisplayCratesAndSleep("DONE!", "DONE!");

    // Little extra sleep time before dumping back to prompt
    usleep(sleepTimeMicroseconds);
}

void executeMove(MoveInstruction instruction, string currentInstructionText, string nextInstructionText)
{
    // Display once for the first line of instructions (padding) that we added at the top of ProcessList()
    if (instruction.Quantity == 0) DisplayCratesAndSleep(currentInstructionText, nextInstructionText);

    for (int i = 0; i < instruction.Quantity; i++)
    {
        // Find what is the lowest free position in the destination column
        int yPositionToMoveTo = getLowestFreePositionInColumn(instruction.DestinationColumn);

        // Find out what box is on top of source column
        int yPositionToMoveFrom = getTopBoxYPositionInColumn(instruction.SourceColumn);

        char boxLetter = getTopBoxLetterInColumn(instruction.SourceColumn);

        // Move box
        eraseBoxAt(instruction.SourceColumn, yPositionToMoveFrom);
        createBoxAt(instruction.DestinationColumn, yPositionToMoveTo, boxLetter);

        DisplayCratesAndSleep(currentInstructionText, nextInstructionText);

        system("cls");
    }
}

void DisplayCratesAndSleep(string currentInstructionText, string nextInstructionText)
{
    printList(cratesAscii);

    cout << "Current: " << currentInstructionText << endl << endl;

    cout << "Next: " << nextInstructionText << endl << endl;

    usleep(sleepTimeMicroseconds);
}

void createBoxAt(int column, int yPosition, char letterOnBox)
{
    int xPosition = calculateColumnXPosition(column);

    string currentLine = getListEntryAt(cratesAscii, yPosition);

    currentLine[xPosition - 1] = '[';
    currentLine[xPosition] = letterOnBox;
    currentLine[xPosition + 1] = ']';

    cratesAscii = replaceEntryAt(cratesAscii, yPosition, currentLine);
}

void eraseBoxAt(int column, int yPosition)
{
    int xPosition = calculateColumnXPosition(column);

    string currentLine = getListEntryAt(cratesAscii, yPosition);

    currentLine[xPosition - 1] = ' ';
    currentLine[xPosition] = ' ';
    currentLine[xPosition + 1] = ' ';

    cratesAscii = replaceEntryAt(cratesAscii, yPosition, currentLine);
}

char getTopBoxLetterInColumn(int column)
{
    int xPosition = calculateColumnXPosition(column);

    for (int i = 0; i < cratesAscii.size(); i++)
    {
        string currentLine = getListEntryAt(cratesAscii, i);

        char currentCharacterFound = currentLine[xPosition];

        // cout << "Looking at column " << column << " X position: " << xPosition << " character found: " << currentCharacterFound << endl;

        if (isalpha(currentCharacterFound))
            return currentCharacterFound;
    }

    return '!';
}

int getTopBoxYPositionInColumn(int column)
{
    int xPosition = calculateColumnXPosition(column);

    for (int i = 0; i < cratesAscii.size(); i++)
    {
        string currentLine = getListEntryAt(cratesAscii, i);

        char currentCharacterFound = currentLine[xPosition];

        // cout << "Looking at column " << column << " X position: " << xPosition << " character found: " << currentCharacterFound << endl;

        if (isalpha(currentCharacterFound))
            return i;
    }

    return 2;
}

int getLowestFreePositionInColumn(int column)
{
    int xPosition = calculateColumnXPosition(column);

    for (int i = 0; i < cratesAscii.size(); i++)
    {
        string currentLine = getListEntryAt(cratesAscii, i);

        char currentCharacterFound = currentLine[xPosition];

        // cout << "Looking at column " << column << " X position: " << xPosition << " character found: " << currentCharacterFound << endl;

        if (currentCharacterFound == intToChar(column))
            return i - 1;

        if (isalpha(currentCharacterFound))
            return i - 1;
    }

    return 2;
}

int calculateColumnXPosition(int column)
{
    // X: Column 1 = 1
    // X: Column 2 = 5
    // X: Column 2 = 9

    // Columns are 4 characters apart

    int leftmostColumnXPosition = 1;

    int xPosition;

    if (column == 1)
    {
        xPosition = leftmostColumnXPosition;
    }
    else
    {
        xPosition = leftmostColumnXPosition + (4 * (column - 1));
    }

    return xPosition;
}

MoveInstruction parseMoveInstruction(string instructionLine)
{
    MoveInstruction returnMoveInstruction;

    // Return dummy values to handle padding at beginning of instructions list
    if (instructionLine.size() == 0)
    {
        returnMoveInstruction.Quantity = 0;
        returnMoveInstruction.SourceColumn = 1;
        returnMoveInstruction.DestinationColumn = 1;

        return returnMoveInstruction;
    }

    // Start at a position such that we skip "move " and start at the first number
    int currentPosition = 5;

    string parsedQuantityNumber = "";
    while (isdigit(instructionLine[currentPosition]))
    {
        parsedQuantityNumber += instructionLine[currentPosition];
        currentPosition++;
    }

    returnMoveInstruction.Quantity = stoi(parsedQuantityNumber);

    // Advance position until we start finding numbers again
    while (!isdigit(instructionLine[currentPosition]))
    {
        currentPosition++;
    }

    // Parse the from column
    string parsedSourceColumnNumber = "";
    while (isdigit(instructionLine[currentPosition]))
    {
        parsedSourceColumnNumber += instructionLine[currentPosition];
        currentPosition++;
    }

    returnMoveInstruction.SourceColumn = stoi(parsedSourceColumnNumber);

    // Advance position until we start finding numbers again
    while (!isdigit(instructionLine[currentPosition]))
    {
        currentPosition++;
    }

    // Parse the destination column
    string parsedDestinationColumnNumber = "";
    while (isdigit(instructionLine[currentPosition]))
    {
        parsedDestinationColumnNumber += instructionLine[currentPosition];
        currentPosition++;
    }

    returnMoveInstruction.DestinationColumn = stoi(parsedDestinationColumnNumber);

    return returnMoveInstruction;
}

void printList(list<string> listToPrint)
{
    for (int i = 0; i < listToPrint.size(); i++)
    {
        cout << getListEntryAt(listToPrint, i) << endl;
    }

    cout << endl;
}

list<string> getInstructionsPartOfData()
{
    list<string> returnList;

    bool foundBlankLineFlag = false;

    for (int i = 0; i < allLines.size(); i++)
    {
        string fullLine = getListEntryAt(allLines, i);

        if (fullLine[0] == '\0')
        {
            foundBlankLineFlag = true;
            continue;
        }

        if (foundBlankLineFlag)
            returnList.push_back(fullLine);
    }

    return returnList;
}

list<string> getAsciiCratesPartOfData()
{
    list<string> returnList;

    // Set up padding lines to be same width as crate lines
    string paddingLine = "";

    string lineForWidthReference = getListEntryAt(allLines, 0);

    for (int i = 0; i < lineForWidthReference.size(); i++)
    {
        paddingLine += " ";
    }

    // Add blank lines above for useful space
    for (int i = 0; i < blankLinesOnTop; i ++)
    {
        returnList.push_back(paddingLine);
    }

    for (int i = 0; i < allLines.size(); i ++)
    {
        string fullLine = getListEntryAt(allLines, i);

        if (fullLine[0] == '\0')
            break;

        returnList.push_back(fullLine);
    }

    return returnList;
}

list<string> replaceEntryAt(list<string> inputList, int index, string replacementEntry)
{
    // Remove old line
    list<string>::iterator itForRemove = inputList.begin();

    for(int i = 0; i < index; i++)
        ++itForRemove;

    inputList.erase(itForRemove);

    // Replace with new line
    list<string>::iterator it = inputList.begin();

    for(int i = 0; i < index; i++)
        ++it;

    inputList.insert(it, replacementEntry);

    return inputList;
}

string getListEntryAt(list<string> inputList, int index)
{
    list<string>::iterator it = inputList.begin();

    for(int i = 0; i < index; i++)
        ++it;

    return *it;
}

char intToChar(int input)
{
    if (input > 9 || input < 0) throw "Cannot convert non single digit ints to char";

    string buf = "";
    char str[20];
    buf += itoa(input, str, 10);

    return buf[0];
}

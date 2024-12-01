#include <iostream>
#include <sstream>
#include <list>
#include <unistd.h>

#include "RawData/RawData.h"
#include "Models/MoveInstruction.h"
#include "Models/Crane.h"
#include "Logic/CraneHandler.h"
#include "Logic/StringListHelpers.h"

using namespace std;

list<string> replaceEntryAt(list<string> inputList, int index, string replacementEntry);

void processList();

list<string> getAsciiCratesPartOfData();
list<string> getInstructionsPartOfData();

MoveInstruction parseMoveInstruction(string instructionLine);

void executeMove(MoveInstruction instruction, string currentInstructionText, string nextInstructionText);

int getLowestFreePositionInColumn(int column);
int getTopBoxYPositionInColumn(int column);
char getTopBoxLetterInColumn(int column);

int calculateColumnXPosition(int column);

char intToChar(int input);

void DisplayCratesAndSleep(string currentInstructionText, string nextInstructionText);

int yPositionToMoveTo = 0;

list<string> _cratesAscii;
list<string> _allLines;

Crane _crane;

CraneHandler _craneHandler;

int blankLinesOnTop = 45;
int sleepTimeMicroseconds = 50000;
// 100000

int main()
{
    system("cls");

    string line;
    istringstream f(RawData::INPUT_DATA_RAW);

    while (getline(f, line))
    {
        _allLines.push_back(line);
    }

    processList();

    return 0;
}

void processList()
{
    _cratesAscii = getAsciiCratesPartOfData();
    list<string> instructionsRaw = getInstructionsPartOfData();

    instructionsRaw.push_front(""); // Padding because we're showing current and next instructions each round

    _craneHandler.Initialize(_crane, _cratesAscii);
    //StringListHelpers()Initialize(_craneHandler);

    DisplayCratesAndSleep("TEST", "TEST");

    int i = 0;

    do
    {
        string currentInstructionText = StringListHelpers().GetListEntryAt(instructionsRaw, i);

        MoveInstruction currentMove = parseMoveInstruction(currentInstructionText);

        // All rounds other than the second to last and last rounds
        if (i < instructionsRaw.size() - 1)
        {
            string nextInstructionText = StringListHelpers().GetListEntryAt(instructionsRaw, i + 1);

            executeMove(currentMove, currentInstructionText, nextInstructionText);

            continue;
        }

        // For the second to last round, say done instead
        if (i == instructionsRaw.size() - 1)
        {
            executeMove(currentMove, currentInstructionText, "DONE!");
        }
    }
    while (++i < instructionsRaw.size());

    // Little extra sleep time before dumping back to prompt
    usleep(sleepTimeMicroseconds * 1000000);
}

void executeMove(MoveInstruction instruction, string currentInstructionText, string nextInstructionText)
{
    // Display once for the first line of instructions (padding) that we added at the top of ProcessList()
    if (instruction.Quantity == 0) DisplayCratesAndSleep(currentInstructionText, nextInstructionText);

    if (_craneHandler.GetCraneY() == 0)
        _craneHandler.SetCranePosition(_craneHandler.CalculateColumnXPosition(instruction.SourceColumn), 0);

    // Find out what box is on top of source column
    int yPositionToMoveFrom = _craneHandler.GetTopBoxYPositionInColumn(instruction.SourceColumn);

    list<char> boxLetter = _craneHandler.GetBoxLettersToPickUp(instruction.SourceColumn, instruction.Quantity);

    // Find what is the lowest free position in the destination column
    if (!_craneHandler.GetCraneIsBoxGrabbed())
        yPositionToMoveTo = _craneHandler.GetLowestFreePositionInColumn(instruction.DestinationColumn);

    _craneHandler.SetTallestBoxHeight();

    _craneHandler.SetCraneDestinationX(_craneHandler.CalculateColumnXPosition(instruction.SourceColumn));

    _craneHandler.AnimateMoveHorizontally(sleepTimeMicroseconds, currentInstructionText, nextInstructionText);

    _craneHandler.SetCraneDestinationY(yPositionToMoveFrom - 1);

    _craneHandler.AnimateMoveVertically(sleepTimeMicroseconds, currentInstructionText, nextInstructionText);

    _craneHandler.GrabBoxes(instruction.Quantity);

    _craneHandler.SetCraneDestinationToSafeHeight();

    _craneHandler.AnimateMoveVertically(sleepTimeMicroseconds, currentInstructionText, nextInstructionText);

    _craneHandler.SetCraneDestinationX(_craneHandler.CalculateColumnXPosition(instruction.DestinationColumn));

    _craneHandler.AnimateMoveHorizontally(sleepTimeMicroseconds, currentInstructionText, nextInstructionText);

    _craneHandler.SetCraneDestinationY(yPositionToMoveTo - instruction.Quantity);

    _craneHandler.AnimateMoveVertically(sleepTimeMicroseconds, currentInstructionText, nextInstructionText);

    _craneHandler.ReleaseBoxes();

    _craneHandler.SetTallestBoxHeight();
    _craneHandler.SetCraneDestinationToSafeHeight();

    _craneHandler.AnimateMoveVertically(sleepTimeMicroseconds, currentInstructionText, nextInstructionText);
}

void DisplayCratesAndSleep(string currentInstructionText, string nextInstructionText)
{
    StringListHelpers().PrintList(_cratesAscii);

    cout << "Current: " << currentInstructionText << endl << endl;

    cout << "Next: " << nextInstructionText << endl << endl;

    //usleep(sleepTimeMicroseconds);
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

list<string> getInstructionsPartOfData()
{
    list<string> returnList;

    bool foundBlankLineFlag = false;

    for (int i = 0; i < _allLines.size(); i++)
    {
        string fullLine = StringListHelpers().GetListEntryAt(_allLines, i);

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
    string paddingLine;

    string lineForWidthReference = StringListHelpers::GetListEntryAt(_allLines, 0);

    for (int i = 0; i < lineForWidthReference.size(); i++)
    {
        paddingLine += " ";
    }

    // Add blank lines above for useful space
    for (int i = 0; i < blankLinesOnTop; i ++)
    {
        returnList.push_back(paddingLine);
    }

    for (int i = 0; i < _allLines.size(); i ++)
    {
        string fullLine = StringListHelpers::GetListEntryAt(_allLines, i);

        if (fullLine[0] == '\0')
            break;

        returnList.push_back(fullLine);
    }

    return returnList;
}
#include <iostream>
#include <list>
#include <unistd.h>
#include "CraneHandler.h"

using namespace std;

void CraneHandler::Initialize(Crane craneToMove, std::list<string> cratesAscii)
{
    _crane = craneToMove;
    _cratesAscii = cratesAscii;

    _consoleHelpers.Initialize();
}

void CraneHandler::SetCranePosition(int x, int y)
{
    _crane.CurrentXPosition = x;
    _crane.CurrentYPosition = y;

    _crane.IsMoving = false;
}

void CraneHandler::SetCraneDestinationToSafeHeight()
{
    _crane.DestinationYPosition = _crane.TallestBoxHeight - 4;

    _crane.IsMoving = true;
}

void CraneHandler::SetCraneDestinationX(int x)
{
    _crane.DestinationXPosition = x;
    _crane.DestinationYPosition = _crane.CurrentYPosition;

    if (_crane.CurrentXPosition != _crane.DestinationXPosition)
    {
        _crane.IsMoving = true;

        return;
    }

    _crane.IsMoving = false;
}

int CraneHandler::GetCraneY()
{
    return _crane.CurrentYPosition;
}

bool CraneHandler::GetCraneIsBoxGrabbed()
{
    return _crane.IsBoxGrabbed;
}

void CraneHandler::SetCraneDestinationY(int y)
{
    _crane.DestinationXPosition = _crane.CurrentXPosition;
    _crane.DestinationYPosition = y;

    if (_crane.CurrentYPosition != _crane.DestinationYPosition)
    {
        _crane.IsMoving = true;

        return;
    }

    _crane.IsMoving = false;
}

void CraneHandler::AnimateMoveVertically(int microsecondsBetweenFrames, std::string currentInstructionText, std::string nextInstructionText)
{
    while (_crane.IsMoving)
    {
        // Add _crane to _cratesAscii
        EraseCraneOnCratesAscii();
        MoveCraneNextStepVertically();
        DrawCraneOnCratesAscii();

        string currentMovePlaintext = "Current: " + currentInstructionText;
        string blankLine = "                                                  "; // Yes I'm just being obtuse at this point

        int yPositionToDrawMessageAt = _cratesAscii.size() + 2;

        DrawStringInConsole(blankLine, 0, yPositionToDrawMessageAt);
        DrawStringInConsole(currentMovePlaintext, 0, yPositionToDrawMessageAt);

        DrawStringInConsole(blankLine, 0, yPositionToDrawMessageAt + 2);
        DrawStringInConsole("Next: " + nextInstructionText, 0, yPositionToDrawMessageAt + 2);

        usleep(microsecondsBetweenFrames);

        // Stop if we reached our destination
        if (_crane.CurrentYPosition == _crane.DestinationYPosition)
        {
            _crane.IsMoving = false;
        }
    }
}

void CraneHandler::AnimateMoveHorizontally(int microsecondsBetweenFrames, std::string currentInstructionText, std::string nextInstructionText)
{
    while (_crane.IsMoving)
    {
        if (_crane.LastXPosition == 0) _crane.LastXPosition = _crane.CurrentXPosition;

        // Add _crane to _cratesAscii
        EraseCraneOnCratesAscii();
        MoveCraneNextStepHorizontally();
        DrawCraneOnCratesAscii();

        string currentMovePlaintext = "Current: " + currentInstructionText;
        string blankLine = "                                                  "; // Yes I'm just being obtuse at this point

        int yPositionToDrawMessageAt = _cratesAscii.size() + 2;

        DrawStringInConsole(blankLine, 0, yPositionToDrawMessageAt);
        DrawStringInConsole(currentMovePlaintext, 0, yPositionToDrawMessageAt);

        DrawStringInConsole(blankLine, 0, yPositionToDrawMessageAt + 2);
        DrawStringInConsole("Next: " + nextInstructionText, 0, yPositionToDrawMessageAt + 2);

        usleep(microsecondsBetweenFrames);

        // Stop if we reached our destination
        if (_crane.CurrentXPosition == _crane.DestinationXPosition)
        {
            _crane.IsMoving = false;
        }
    }
}

void CraneHandler::DrawCraneOnCratesAscii()
{
    // Draw body
    for (int i = 0; i < _crane.CurrentYPosition; i++)
    {
        _consoleHelpers.DrawCharacterAt('|', _crane.CurrentXPosition, i);
    }

    _consoleHelpers.DrawCharacterAt('^', _crane.CurrentXPosition, _crane.CurrentYPosition);

    if (_crane.IsBoxGrabbed)
        DrawBoxInConsole(_crane.BoxLetterGrabbed, _crane.CurrentXPosition, _crane.CurrentYPosition + 1);
}

void CraneHandler::EraseCraneOnCratesAscii()
{
    // Draw body
    for (int i = 0; i < _crane.CurrentYPosition; i++)
    {
        _consoleHelpers.DrawCharacterAt(' ', _crane.CurrentXPosition, i);
    }

    _consoleHelpers.DrawCharacterAt(' ', _crane.CurrentXPosition, _crane.CurrentYPosition);

    if (_crane.IsBoxGrabbed)
        EraseBoxInConsole(_crane.CurrentXPosition, _crane.CurrentYPosition + 1);
}

void CraneHandler::MoveCraneNextStepVertically()
{
    if (_crane.DestinationYPosition > _crane.CurrentYPosition)
        _crane.CurrentYPosition++;

    if (_crane.DestinationYPosition < _crane.CurrentYPosition)
        _crane.CurrentYPosition--;
}

void CraneHandler::MoveCraneNextStepHorizontally()
{
    if (_crane.DestinationXPosition > _crane.CurrentXPosition)
        _crane.CurrentXPosition++;

    if (_crane.DestinationXPosition < _crane.CurrentXPosition)
        _crane.CurrentXPosition--;
}

void CraneHandler::DrawBoxInConsole(char grabbedBoxLetter, int x, int y)
{
    _consoleHelpers.DrawCharacterAt('[', _crane.CurrentXPosition - 1, _crane.CurrentYPosition + 1);
    _consoleHelpers.DrawCharacterAt(grabbedBoxLetter, _crane.CurrentXPosition, _crane.CurrentYPosition + 1);
    _consoleHelpers.DrawCharacterAt(']', _crane.CurrentXPosition + 1, _crane.CurrentYPosition + 1);
}

void CraneHandler::EraseBoxInConsole(int x, int y)
{
    _consoleHelpers.DrawCharacterAt(' ', _crane.CurrentXPosition - 1, _crane.CurrentYPosition + 1);
    _consoleHelpers.DrawCharacterAt(' ', _crane.CurrentXPosition, _crane.CurrentYPosition + 1);
    _consoleHelpers.DrawCharacterAt(' ', _crane.CurrentXPosition + 1, _crane.CurrentYPosition + 1);
}

void CraneHandler::GrabBox()
{
    _crane.IsBoxGrabbed = true;

    string currentLine = StringListHelpers().GetListEntryAt(_cratesAscii, _crane.CurrentYPosition + 1);

    _crane.BoxLetterGrabbed = currentLine[_crane.CurrentXPosition];

    // Erase it in the actual cratesAscii list<string>
    currentLine[_crane.CurrentXPosition - 1] = ' ';
    currentLine[_crane.CurrentXPosition] = ' ';
    currentLine[_crane.CurrentXPosition + 1] = ' ';

    _cratesAscii = StringListHelpers().ReplaceEntryAt(_cratesAscii, _crane.CurrentYPosition + 1, currentLine);
}

void CraneHandler::ReleaseBox()
{
    _crane.IsBoxGrabbed = false;

    // Now draw it in the actual cratesAscii list<string>
    string currentLine = StringListHelpers().GetListEntryAt(_cratesAscii, _crane.CurrentYPosition + 1);

    currentLine[_crane.CurrentXPosition - 1] = '[';
    currentLine[_crane.CurrentXPosition] = _crane.BoxLetterGrabbed;
    currentLine[_crane.CurrentXPosition + 1] = ']';

    _cratesAscii = StringListHelpers().ReplaceEntryAt(_cratesAscii, _crane.CurrentYPosition + 1, currentLine);

    _crane.BoxLetterGrabbed = '!';
}

void CraneHandler::SetTallestBoxHeight()
{
    for (int i = 0; i < _cratesAscii.size(); i++)
    {
        string currentLine = StringListHelpers().GetListEntryAt(_cratesAscii, i);

        for (int j = 0; j < currentLine.size(); j++)
        {
            if (isalpha(currentLine[j]))
            {
                _crane.TallestBoxHeight = i;
                return;
            }
        }
    }

    throw out_of_range("Could not find any boxes in _cratesAscii");
}

char CraneHandler::GetTopBoxLetterInColumn(int column)
{
    int xPosition = CalculateColumnXPosition(column);

    for (int i = 0; i < _cratesAscii.size(); i++)
    {
        string currentLine = StringListHelpers().GetListEntryAt(_cratesAscii, i);

        char currentCharacterFound = currentLine[xPosition];

        // cout << "Looking at column " << column << " X position: " << xPosition << " character found: " << currentCharacterFound << endl;

        if (isalpha(currentCharacterFound))
            return currentCharacterFound;
    }

    return '!';
}

int CraneHandler::GetTopBoxYPositionInColumn(int column)
{
    int xPosition = CalculateColumnXPosition(column);

    for (int i = 0; i < _cratesAscii.size(); i++)
    {
        string currentLine = StringListHelpers().GetListEntryAt(_cratesAscii, i);

        char currentCharacterFound = currentLine[xPosition];

        // cout << "Looking at column " << column << " X position: " << xPosition << " character found: " << currentCharacterFound << endl;

        if (isalpha(currentCharacterFound))
            return i;
    }

    return 2;
}

int CraneHandler::GetLowestFreePositionInColumn(int column)
{
    int xPosition = CalculateColumnXPosition(column);

    for (int i = 0; i < _cratesAscii.size(); i++)
    {
        string currentLine = StringListHelpers().GetListEntryAt(_cratesAscii, i);

        char currentCharacterFound = currentLine[xPosition];

        // cout << "Looking at column " << column << " X position: " << xPosition << " character found: " << currentCharacterFound << endl;

        if (currentCharacterFound == IntToChar(column))
            return i - 1;

        if (isalpha(currentCharacterFound))
            return i - 1;
    }

    return 2;
}

int CraneHandler::CalculateColumnXPosition(int column)
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

char CraneHandler::IntToChar(int input)
{
    if (input > 9 || input < 0) out_of_range("Cannot convert non single digit ints to char");

    string buf = "";
    char stringBuffer[20];
    buf += itoa(input, stringBuffer, 10);

    return buf[0];
}

void CraneHandler::DrawStringInConsole(std::string message, int startX, int startY)
{
    for (int x = 0; x < message.size(); x++)
    {
        _consoleHelpers.DrawCharacterAt(message[x], startX + x, startY);
    }
}

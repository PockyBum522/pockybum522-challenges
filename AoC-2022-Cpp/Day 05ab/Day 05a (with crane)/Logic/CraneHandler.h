#ifndef DAY_01_CRANEHANDLER_H
#define DAY_01_CRANEHANDLER_H

#include "../Models/Crane.h"
#include "StringListHelpers.h"
#include "ConsoleHelpers.h"

class CraneHandler
{
private:
    ConsoleHelpers _consoleHelpers;

    Crane _crane;

    std::list<std::string> _cratesAscii;

    void DrawCraneOnCratesAscii();

    void EraseCraneOnCratesAscii();

    void DrawBoxInConsole(char grabbedBoxLetter, int x, int y);

    void EraseBoxInConsole(int x, int y);

    void MoveCraneNextStepVertically();

    void MoveCraneNextStepHorizontally();

    char IntToChar(int input);

public:
    void Initialize(Crane craneToMove, std::list<std::string> cratesAscii);

    void SetCranePosition(int x, int y);

    void SetCraneDestinationX(int x);

    void SetCraneDestinationY(int y);

    int GetCraneY();

    bool GetCraneIsBoxGrabbed();

    void SetCraneDestinationToSafeHeight();

    void AnimateMoveVertically(int microsecondsBetweenFrames, std::string currentInstructionText, std::string nextInstructionText);

    void AnimateMoveHorizontally(int microsecondsBetweenFrames, std::string currentInstructionText, std::string nextInstructionText);

    void GrabBox();

    void ReleaseBox();

    void SetTallestBoxHeight();

    int CalculateColumnXPosition(int column);

    int GetTopBoxYPositionInColumn(int column);

    char GetTopBoxLetterInColumn(int column);

    int GetLowestFreePositionInColumn(int column);

    void DrawCharacterAt(char toDraw, int drawAtX, int drawAtY);

    void DrawStringInConsole(std::string basicString, int i, int i1);
};

#endif //DAY_01_CRANEHANDLER_H
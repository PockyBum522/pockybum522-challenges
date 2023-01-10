#include "ListProcessor.h"
#include "ListHelpers/CharListHelpers.h"
#include "../LoggerConsole/LoggerConsole.h"
#include "../Models/Board.h"
#include "../Models/Rope.h"

using namespace std;

void ListProcessor::ProcessList(list<string>& inputList)
{
    LoggerConsole::ConsoleLogMessagesEnabled = true;

    LoggerConsole::WriteLine("Initializing rope...");

    Rope rope = Rope();

    LoggerConsole::WriteLine("Initializing board...");

    int boardDimensions = 300;

    Board board(boardDimensions, boardDimensions, rope);

    board.Squares[boardDimensions / 2][boardDimensions / 2].SymbolToShow = 's';

    LoggerConsole::WriteLine("Printing board to console...");

    board.RopeToMove.headXPosition = boardDimensions / 2;
    board.RopeToMove.headYPosition = boardDimensions / 2;

    board.RopeToMove.tailXPosition = boardDimensions / 2;
    board.RopeToMove.tailYPosition = boardDimensions / 2;

    if (LoggerConsole::ConsoleLogMessagesEnabled)
        board.WriteBoardToConsole();

    for (auto line : inputList)
    {
        // Move head
        char directionChar = GetDirectionCharacterFromLine(line);

        int numberOfTimesToMove = GetNumberOfMovesFromLine(line);

        for (int i = numberOfTimesToMove; i > 0; i--)
        {
            string directionString = "";
            directionString += directionChar;

            LoggerConsole::WriteLine("Moving head " + directionString + " " + to_string(i) + " more times.");

            board.RopeToMove.MoveHeadOneSpace(directionChar);

            board.EnsureHeadIsWithinBounds();

            if (LoggerConsole::ConsoleLogMessagesEnabled)
                board.WriteBoardToConsole();

            // Move tail
            LoggerConsole::WriteLine("Moving tail.");

            board.RopeToMove.MoveTailToFollowHead();

            board.MarkCurrentTailSpaceAsVisited();

            if (LoggerConsole::ConsoleLogMessagesEnabled)
                board.WriteBoardToConsole();
        }
    }

    if (LoggerConsole::ConsoleLogMessagesEnabled)
        board.WriteBoardToConsoleWithoutRope();

    int answer = board.GetNumberOfSquaresVisitedAtLeastOnceByTail();
    LoggerConsole::WriteLine("Tail visited: " + to_string(answer) + " squares at least once.", 1 , true);
}

char ListProcessor::GetDirectionCharacterFromLine(string dataLine)
{
    return dataLine[0];
}

int ListProcessor::GetNumberOfMovesFromLine(string dataLine)
{
    string currentlyParsedChars;

    for (int i = 0; i < dataLine.size(); i++)
    {
        if (isdigit(dataLine[i]))
            currentlyParsedChars += dataLine[i];
    }

    return stoi(currentlyParsedChars);
}

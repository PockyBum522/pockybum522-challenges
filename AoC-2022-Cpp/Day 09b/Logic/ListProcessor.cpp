#include "ListProcessor.h"
#include "ListHelpers/CharListHelpers.h"
#include "../LoggerConsole/LoggerConsole.h"
#include "../Models/Board.h"
#include "../Models/Rope.h"
#include "../RawData/RawDataLoader/RawDataLoader.h"
#include "../RawData/RawData.h"

using namespace std;

void ListProcessor::ProcessList()
{
    list<string> inputList = RawDataLoader::LoadRawDataIntoList(RawData::INPUT_DATA_RAW);

    LoggerConsole::ConsoleLogMessagesEnabled = false;

    LoggerConsole::WriteLine("Initializing rope...");

    int boardDimensions = 300;
    Rope rope = Rope(10, boardDimensions);

    LoggerConsole::WriteLine("Initializing board...");

    Board board(boardDimensions, boardDimensions, rope);

    board.Squares[boardDimensions / 2][boardDimensions / 2].SymbolToShow = 's';

    LoggerConsole::WriteLine("Printing board to console...");

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
    LoggerConsole::WriteLine("RopeSegments visited: " + to_string(answer) + " squares at least once.", 1 , true);
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

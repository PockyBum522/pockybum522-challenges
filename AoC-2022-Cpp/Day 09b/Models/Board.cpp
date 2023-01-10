#include <iostream>
#include <utility>
#include "Board.h"

using namespace std;

Board::Board(int rows, int columns, Rope rope) : RopeToMove(std::move(rope))
{
    Rows = rows;
    Columns = columns;

    InitializeBoardSquares();
}

void Board::InitializeBoardSquares()
{
    vector<BoardSquare> currentRow;

    for (int y = 0; y < Rows; y++)
    {
        for (int x = 0; x < Columns; x++)
        {
            currentRow.emplace_back(BoardSquare());
        }

        Squares.emplace_back(currentRow);
    }
}

void Board::WriteBoardToConsole()
{
    auto head = RopeToMove.RopeSegments[0];

    for (int y = 0; y < Rows; y++)
    {
        for (int x = 0; x < Columns; x++)
        {
            PrintTopmostSegmentOrSquareSymbolAt(x, y);
        }

        cout << endl;
    }

    cout << endl;
}

void Board::WriteBoardToConsoleWithoutRope()
{
    for (int y = 0; y < Rows; y++)
    {
        for (int x = 0; x < Columns; x++)
        {
            cout << Squares[x][y].SymbolToShow;
        }

        cout << endl;
    }

    cout << endl;
}

void Board::MarkCurrentTailSpaceAsVisited()
{
    auto& tailSegment09 = RopeToMove.RopeSegments[9];

    Squares[tailSegment09.CurrentX][tailSegment09.CurrentY].VisitedByTail = true;

    if (Squares[tailSegment09.CurrentX][tailSegment09.CurrentY].SymbolToShow == '.')
        Squares[tailSegment09.CurrentX][tailSegment09.CurrentY].SymbolToShow = '#';
}

int Board::GetNumberOfSquaresVisitedAtLeastOnceByTail()
{
    int squaresVisited = 0;

    for (int y = 0; y < Rows; y++)
    {
        for (int x = 0; x < Columns; x++)
        {
            if (!Squares[x][y].VisitedByTail) continue;

            squaresVisited++;
        }
    }

    return squaresVisited;
}

void Board::EnsureHeadIsWithinBounds() const
{
    auto head = RopeToMove.RopeSegments[0];

    if (head.CurrentX > Columns)
        throw invalid_argument("Rope head moved outside the board too far to the right!");

    if (head.CurrentX < 0)
        throw invalid_argument("Rope head moved outside the board too far to the left!");

    if (head.CurrentY > Rows)
        throw invalid_argument("Rope head moved outside the board too far to the south!");

    if (head.CurrentY < 0)
        throw invalid_argument("Rope head moved outside the board too far to the north!");
}

void Board::PrintTopmostSegmentOrSquareSymbolAt(int x, int y)
{
    int numberOfSegments = (int)RopeToMove.RopeSegments.size();

    for (int i = 0; i < numberOfSegments; i++)
    {
        if (RopeToMove.RopeSegments[i].CurrentX == x &&
            RopeToMove.RopeSegments[i].CurrentY == y)
        {
            cout << RopeToMove.RopeSegments[i].SegmentLabel;
            return;
        }
    }

    cout << Squares[x][y].SymbolToShow;
}

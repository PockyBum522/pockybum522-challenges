#include <iostream>
#include "Board.h"

using namespace std;

Board::Board(int rows, int columns, Rope rope)
{
    Rows = rows;
    Columns = columns;

    RopeToMove = rope;

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
    for (int y = 0; y < Rows; y++)
    {
        for (int x = 0; x < Columns; x++)
        {
            if (x == RopeToMove.headXPosition &&
                y == RopeToMove.headYPosition)
            {
                cout << "H";
            }
            else if (x == RopeToMove.tailXPosition &&
                     y == RopeToMove.tailYPosition)
            {
                cout << "T";
            }
            else
            {
                cout << Squares[x][y].SymbolToShow;
            }
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
    Squares[RopeToMove.tailXPosition][RopeToMove.tailYPosition].VisitedByTail = true;

    if (Squares[RopeToMove.tailXPosition][RopeToMove.tailYPosition].SymbolToShow == '.')
        Squares[RopeToMove.tailXPosition][RopeToMove.tailYPosition].SymbolToShow = '#';
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
    if (RopeToMove.headXPosition > Columns)
        throw invalid_argument("Rope head moved outside the board too far to the right!");

    if (RopeToMove.headXPosition < 0)
        throw invalid_argument("Rope head moved outside the board too far to the left!");

    if (RopeToMove.headYPosition > Rows)
        throw invalid_argument("Rope head moved outside the board too far to the south!");

    if (RopeToMove.headYPosition < 0)
        throw invalid_argument("Rope head moved outside the board too far to the north!");
}

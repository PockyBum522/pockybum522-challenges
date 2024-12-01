#ifndef DAY_01_BOARD_H
#define DAY_01_BOARD_H

#include <vector>
#include "BoardSquare.h"
#include "Rope.h"

using namespace std;

class Board
{
public:
    Board(int rows, int columns, Rope rope);

    int Rows;
    int Columns;

    Rope RopeToMove;

    vector<vector<BoardSquare>> Squares;

    void WriteBoardToConsole();

    void MarkCurrentTailSpaceAsVisited();

    void WriteBoardToConsoleWithoutRope();

    int GetNumberOfSquaresVisitedAtLeastOnceByTail();

    void EnsureHeadIsWithinBounds() const;

private:
    void InitializeBoardSquares();
};


#endif //DAY_01_BOARD_H

//
// Created by David on 12/31/2022.
//

#ifndef DAY_01_BOARDSQUARE_H
#define DAY_01_BOARDSQUARE_H


class BoardSquare
{
public:
    BoardSquare(char symbolToShow = '.', bool visitedByTail = false);

    char SymbolToShow;

    bool VisitedByTail;
};


#endif //DAY_01_BOARDSQUARE_H

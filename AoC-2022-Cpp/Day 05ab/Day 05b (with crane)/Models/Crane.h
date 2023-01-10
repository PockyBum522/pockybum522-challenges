//
// Created by David on 12/21/2022.
//

#ifndef DAY_01_CRANE_H
#define DAY_01_CRANE_H


#include <list>

class Crane {
public:
    int DestinationXPosition = 0;
    int DestinationYPosition = 0;

    int CurrentXPosition = 0;
    int CurrentYPosition = 0;

    int LastXPosition = 0;

    int TallestBoxHeight = 0;

    bool AreBoxesGrabbed = false;

    bool IsMoving = false;

    std::list<char> BoxLettersGrabbed;
};


#endif //DAY_01_CRANE_H

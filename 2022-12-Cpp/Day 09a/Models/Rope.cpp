//
// Created by David on 12/31/2022.
//

#include "Rope.h"

void Rope::MoveHeadOneSpace(char direction)
{
    switch (direction) \
    {
        case 'U':
            headYPosition--;
            break;

        case 'D':
            headYPosition++;
            break;

        case 'L':
            headXPosition--;
            break;

        case 'R':
            headXPosition++;
            break;
    }
}

void Rope::MoveTailToFollowHead()
{
    // Tail is too far to the right
    if (tailXPosition < headXPosition - 1)
    {
        tailXPosition++;

        // If was diagonal, make it line up
        tailYPosition = headYPosition;
    }

    // Tail is too far to the left
    if (tailXPosition > headXPosition + 1)
    {
        tailXPosition--;

        // If was diagonal, make it line up
        tailYPosition = headYPosition;
    }

    // Tail is too far to the south
    if (tailYPosition < headYPosition - 1)
    {
        tailYPosition++;

        // If was diagonal, make it line up
        tailXPosition = headXPosition;
    }

    // Tail is too far to the north
    if (tailYPosition > headYPosition + 1)
    {
        tailYPosition--;

        // If was diagonal, make it line up
        tailXPosition = headXPosition;
    }
}

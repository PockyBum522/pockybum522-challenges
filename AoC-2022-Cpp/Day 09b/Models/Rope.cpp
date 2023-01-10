//
// Created by David on 12/31/2022.
//

#include <string>
#include <stdexcept>
#include "Rope.h"
#include "../LoggerConsole/LoggerConsole.h"

using namespace std;

Rope::Rope(int numberOfTotalSegments, int boardDimensions)
{
    InitializeRope(numberOfTotalSegments, boardDimensions);
}

void Rope::MoveHeadOneSpace(char direction)
{
    auto& head = RopeSegments[0];

    switch (direction) \
    {
        case 'U':
            head.CurrentY--;
            break;

        case 'D':
            head.CurrentY++;
            break;

        case 'L':
            head.CurrentX--;
            break;

        case 'R':
            head.CurrentX++;
            break;

    default:
        throw invalid_argument("Direction to move invalid");
    }
}

void Rope::MoveTailToFollowHead()
{
    for (int i = 1; i < RopeSegments.size(); i++)
    {
        MoveTailSegmentToFollowHead(RopeSegments[i], RopeSegments[i - 1]);
    }
}

void Rope::MoveTailSegmentToFollowHead(RopeSegment& segmentToMove, RopeSegment& nextClosestSegmentToHead)
{
    if (segmentToMove.CurrentY > nextClosestSegmentToHead.CurrentY + 1 &&
        segmentToMove.CurrentX < nextClosestSegmentToHead.CurrentX - 1)
    {
        // segmentToMove is too far to the south

        LoggerConsole::WriteLine("Moving segment " + to_string(segmentToMove.SegmentNumber) + " north-east");

        segmentToMove.CurrentY--;
        segmentToMove.CurrentX++;
    }
    else if (segmentToMove.CurrentY > nextClosestSegmentToHead.CurrentY + 1 &&
             segmentToMove.CurrentX > nextClosestSegmentToHead.CurrentX + 1)
    {
        // segmentToMove is too far to the south

        LoggerConsole::WriteLine("Moving segment " + to_string(segmentToMove.SegmentNumber) + " north-west");

        segmentToMove.CurrentY--;
        segmentToMove.CurrentX--;
    }
    else if (segmentToMove.CurrentY < nextClosestSegmentToHead.CurrentY - 1 &&
             segmentToMove.CurrentX < nextClosestSegmentToHead.CurrentX - 1)
    {
        // segmentToMove is too far to the south

        LoggerConsole::WriteLine("Moving segment " + to_string(segmentToMove.SegmentNumber) + " south-east");

        segmentToMove.CurrentY++;
        segmentToMove.CurrentX++;
    }
    else if (segmentToMove.CurrentY < nextClosestSegmentToHead.CurrentY - 1 &&
             segmentToMove.CurrentX > nextClosestSegmentToHead.CurrentX + 1)
    {
        // segmentToMove is too far to the south

        LoggerConsole::WriteLine("Moving segment " + to_string(segmentToMove.SegmentNumber) + " south-west");

        segmentToMove.CurrentY++;
        segmentToMove.CurrentX--;
    }
    else if (segmentToMove.CurrentY > nextClosestSegmentToHead.CurrentY + 1)
    {
        // segmentToMove is too far to the south

        LoggerConsole::WriteLine("Moving segment " + to_string(segmentToMove.SegmentNumber) + " north");

        segmentToMove.CurrentY--;

        // If was diagonal, make it line up
        segmentToMove.CurrentX = nextClosestSegmentToHead.CurrentX;
    }
    else if (segmentToMove.CurrentX < nextClosestSegmentToHead.CurrentX - 1)
    {
        // segmentToMove is too far to the left

        LoggerConsole::WriteLine("Moving segment " + to_string(segmentToMove.SegmentNumber) + " right");

        segmentToMove.CurrentX++;

        // If was diagonal, make it line up
        segmentToMove.CurrentY = nextClosestSegmentToHead.CurrentY;
    }
    else if (segmentToMove.CurrentY < nextClosestSegmentToHead.CurrentY - 1)
    {
        // segmentToMove is too far to the north

        LoggerConsole::WriteLine("Moving segment " + to_string(segmentToMove.SegmentNumber) + " south");

        segmentToMove.CurrentY++;

        // If was diagonal, make it line up
        segmentToMove.CurrentX = nextClosestSegmentToHead.CurrentX;
    }
    else if (segmentToMove.CurrentX > nextClosestSegmentToHead.CurrentX + 1)
    {
        // segmentToMove is too far to the right

        LoggerConsole::WriteLine("Moving segment " + to_string(segmentToMove.SegmentNumber) + " left");

        segmentToMove.CurrentX--;

        // If was diagonal, make it line up
        segmentToMove.CurrentY = nextClosestSegmentToHead.CurrentY;
    }
}

void Rope::InitializeRope(int numberOfSegments, int boardDimensions)
{
    for (int i = 0; i < numberOfSegments; i++)
    {
        char label;

        if (i == 0)
        {
            label = 'H';
        }
        else if (i < numberOfSegments)
        {
            label = to_string(i)[0];
        }

        RopeSegments.emplace_back(
                i,
                label,
                boardDimensions / 2,
                boardDimensions / 2);
    }
}



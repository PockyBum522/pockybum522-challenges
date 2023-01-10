#ifndef DAY_01_ROPE_H
#define DAY_01_ROPE_H


#include <vector>
#include "RopeSegment.h"

using namespace std;

class Rope
{
public:
    Rope(int numberOfTotalSegments, int boardDimensions);

    vector<RopeSegment> RopeSegments;

    void MoveHeadOneSpace(char direction);
    void MoveTailToFollowHead();

private:
    void InitializeRope(int numberOfSegments, int i);

    static void MoveTailSegmentToFollowHead(RopeSegment &segmentToMove, RopeSegment &nextClosestSegmentToHead);
};


#endif //DAY_01_ROPE_H
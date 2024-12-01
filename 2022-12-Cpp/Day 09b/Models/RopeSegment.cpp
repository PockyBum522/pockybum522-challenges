//
// Created by David on 1/8/2023.
//

#include "RopeSegment.h"

RopeSegment::RopeSegment(int segmentNumber, char segmentLabel, int initialX, int initialY)
{
    CurrentX = initialX;
    CurrentY = initialY;

    SegmentNumber = segmentNumber;

    SegmentLabel = segmentLabel;
}

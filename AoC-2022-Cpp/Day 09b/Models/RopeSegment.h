//
// Created by David on 1/8/2023.
//

#ifndef DAY_01_ROPESEGMENT_H
#define DAY_01_ROPESEGMENT_H


class RopeSegment
{
public:
    RopeSegment(int segmentNumber, char segmentLabel, int initialX, int initialY);

    int CurrentX;
    int CurrentY;

    int SegmentNumber;

    char SegmentLabel;
};


#endif //DAY_01_ROPESEGMENT_H

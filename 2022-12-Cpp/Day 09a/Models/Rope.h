//
// Created by David on 12/31/2022.
//

#ifndef DAY_01_ROPE_H
#define DAY_01_ROPE_H


class Rope
{
public:
    int headXPosition;
    int headYPosition;

    int tailXPosition;
    int tailYPosition;

    void MoveHeadOneSpace(char direction);
    void MoveTailToFollowHead();

private:

};


#endif //DAY_01_ROPE_H

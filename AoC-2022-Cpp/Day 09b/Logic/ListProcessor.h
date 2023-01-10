//
// Created by David on 12/23/2022.
//

#ifndef DAY_01_LISTPROCESSOR_H
#define DAY_01_LISTPROCESSOR_H

#include <string>
#include <list>

using namespace std;

class ListProcessor
{
public:
    static void ProcessList();

    static char GetDirectionCharacterFromLine(string dataLine);

    static int GetNumberOfMovesFromLine(string dataLine);
};


#endif //DAY_01_LISTPROCESSOR_H

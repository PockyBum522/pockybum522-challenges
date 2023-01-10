//
// Created by David on 12/23/2022.
//

#ifndef DAY_01_LISTPROCESSOR_H
#define DAY_01_LISTPROCESSOR_H

#include <string>
#include <list>

class ListProcessor
{
public:
    static void ProcessList(std::list<std::string> inputList);

    static std::string getPreviousXLetters(std::string inputString, int startPosition, int howManyToGet);

    static bool allLettersAreUnique(std::string basicString);
};


#endif //DAY_01_LISTPROCESSOR_H

#ifndef DAY_01_CHARLISTHELPERS_H
#define DAY_01_CHARLISTHELPERS_H


#include <list>

class CharListHelpers {
public:
    static char GetListEntryAt(std::list<char> inputList, int index);

    static void ClearList(std::list<char> inputList);
};


#endif //DAY_01_CHARLISTHELPERS_H

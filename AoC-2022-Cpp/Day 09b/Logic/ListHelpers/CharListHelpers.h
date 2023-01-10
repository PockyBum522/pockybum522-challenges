#ifndef DAY_01_CHARLISTHELPERS_H
#define DAY_01_CHARLISTHELPERS_H


#include <list>

using namespace std;

class CharListHelpers {
public:
    static char GetListEntryAt(list<char> inputList, int index);

    static void ClearList(list<char> inputList);
};


#endif //DAY_01_CHARLISTHELPERS_H

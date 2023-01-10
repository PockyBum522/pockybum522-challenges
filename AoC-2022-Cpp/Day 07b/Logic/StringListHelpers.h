#ifndef DAY_01_STRINGLISTHELPERS_H
#define DAY_01_STRINGLISTHELPERS_H

#include <string>
#include <list>

using namespace std;

class StringListHelpers
{
public:
    static string GetListEntryAt(list<string> inputList, int index);

    static list<string> ReplaceEntryAt(list<string> inputList, int index, string replacementEntry);
};


#endif //DAY_01_STRINGLISTHELPERS_H

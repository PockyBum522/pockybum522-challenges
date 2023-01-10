#ifndef DAY_01_STRINGLISTHELPERS_H
#define DAY_01_STRINGLISTHELPERS_H

#include <string>
#include <list>

class StringListHelpers
{
public:

    static void PrintList(std::list<std::string> listToPrint);

    static std::string GetListEntryAt(std::list<std::string> inputList, int index);

    static std::list<std::string> ReplaceEntryAt(std::list<std::string> inputList, int index, std::string replacementEntry);
};


#endif //DAY_01_STRINGLISTHELPERS_H

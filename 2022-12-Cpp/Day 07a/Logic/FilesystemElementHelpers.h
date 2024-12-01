#ifndef DAY_01_FILESYSTEMELEMENTHELPERS_H
#define DAY_01_FILESYSTEMELEMENTHELPERS_H


#include "../Models/FilesystemElement.h"

using namespace std;

class FilesystemElementHelpers {
public:
    static list<int> listToSumUnder100000;

    static FilesystemElement GetListEntryAt(FilesystemElement *inputList, int index);

    static int CalculateSizeOfAllChildren(list<FilesystemElement>& topLevelList);

    static string GetFullPathToDirectory(FilesystemElement& directoryToGetPathOf);

    static void WalkAndPrintChildren(list<FilesystemElement>& currentLevelList);
};


#endif //DAY_01_FILESYSTEMELEMENTHELPERS_H

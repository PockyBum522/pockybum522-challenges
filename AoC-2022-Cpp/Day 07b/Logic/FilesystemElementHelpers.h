#ifndef DAY_01_FILESYSTEMELEMENTHELPERS_H
#define DAY_01_FILESYSTEMELEMENTHELPERS_H


#include "../Models/FilesystemElement.h"

using namespace std;

class FilesystemElementHelpers {
public:
    static list<int> ListOfDirectorySizes;

    static const int TotalDiskSize = 70000000;

    static const int TotalDiskSpaceNecessary = 30000000;

    static const int TotalUsedSpace = 42586708;

    static FilesystemElement GetListEntryAt(FilesystemElement *inputList, int index);

    static int CalculateSizeOfAllChildren(list<FilesystemElement>& topLevelList);

    static string GetFullPathToDirectory(FilesystemElement& directoryToGetPathOf);

    static void WalkAndPrintChildren(list<FilesystemElement>& currentLevelList);
};


#endif //DAY_01_FILESYSTEMELEMENTHELPERS_H

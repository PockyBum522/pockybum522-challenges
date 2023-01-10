//
// Created by David on 12/25/2022.
//

#ifndef DAY_01_FilesystemELEMENT_H
#define DAY_01_FilesystemELEMENT_H

#include <string>
#include <list>

using namespace std;

class FilesystemElement
{
public:
    enum ElementTypes { Uninitialized, Directory, File };

    FilesystemElement(string name, FilesystemElement* pParentAddress, ElementTypes elementType, int size = 0);

    // Public fields
    list<FilesystemElement> Children;

    string Name;

    FilesystemElement* pParentAddress;

    ElementTypes Type;

    int Size;
};


#endif //DAY_01_FilesystemELEMENT_H

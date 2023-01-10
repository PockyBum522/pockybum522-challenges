#include <iostream>
#include "FilesystemElementHelpers.h"


using namespace std;

list<int> FilesystemElementHelpers::ListOfDirectorySizes;
const int FilesystemElementHelpers::TotalDiskSize;
const int FilesystemElementHelpers::TotalDiskSpaceNecessary;

FilesystemElement FilesystemElementHelpers::GetListEntryAt(FilesystemElement *parentToSearchIn, int index)
{
    list<FilesystemElement> childrenToSearch = parentToSearchIn->Children;

    auto it = childrenToSearch.begin();

    for(int i = 0; i < index; i++)
        ++it;

    return *it;
}

int FilesystemElementHelpers::CalculateSizeOfAllChildren(list<FilesystemElement>& topLevelList)
{
    int summedSize = 0;

    for(auto & element : topLevelList)
    {
        if (element.Type == FilesystemElement::File)
        {
            summedSize += element.Size;
        }

        if (element.Type == FilesystemElement::Directory)
        {
            int sizeOfDirectory = CalculateSizeOfAllChildren(element.Children);

            summedSize += sizeOfDirectory;
        }
    }

    return summedSize;
}

void FilesystemElementHelpers::WalkAndPrintChildren(list<FilesystemElement>& currentLevelList)
{
    for(auto & element : currentLevelList)
    {
        if (element.Type == FilesystemElement::Directory)
        {
            string fullPathToCurrentDirectory = GetFullPathToDirectory(element);

            cout << "Size of all children in: " << fullPathToCurrentDirectory;

            int sizeOfDirectory = CalculateSizeOfAllChildren(element.Children);

            cout << " is: " << sizeOfDirectory << endl << endl;

            ListOfDirectorySizes.push_back(sizeOfDirectory);

            WalkAndPrintChildren(element.Children);
        }
    }

    cout << "======================= DIR SIZES =======================";

    ListOfDirectorySizes.sort();

    for (auto directorySize : ListOfDirectorySizes)
    {
        int originalFreeSpace = TotalDiskSize - TotalUsedSpace;

        int newFreeSpace = originalFreeSpace + directorySize;

        cout << endl << "Directory size: " << directorySize << " deleting this one results in: ";
        cout << newFreeSpace << " free space. Would this be greater than " << TotalDiskSpaceNecessary;
        cout << "?: " << (newFreeSpace > TotalDiskSpaceNecessary) << endl;
    }
}

string FilesystemElementHelpers::GetFullPathToDirectory(FilesystemElement& directoryToGetPathOf)
{
    FilesystemElement currentElement = directoryToGetPathOf;

    string returnString;

    while (currentElement.pParentAddress != nullptr)
    {
        returnString.insert(0, "/" + currentElement.Name);

        currentElement = *currentElement.pParentAddress;
    }

    if (returnString.empty())
        return "/";

    return returnString;
}

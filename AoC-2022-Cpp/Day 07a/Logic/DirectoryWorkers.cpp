#include <stdexcept>
#include <iostream>
#include "DirectoryWorkers.h"
#include "StringListHelpers.h"
#include "FilesystemElementHelpers.h"

using namespace std;

//FilesystemElement* DirectoryWorkers::GetDirectoryAddressIn(FilesystemElement *parentToSearchIn, string nameToSearch)
//{
//    list<FilesystemElement> childrenToSearch = parentToSearchIn->Children;
//
//    for (int i = 0; i < childrenToSearch.size(); i++)
//    {
//        FilesystemElement currentElement = FilesystemElementHelpers::GetListEntryAt(parentToSearchIn, i);
//        FilesystemElement* currentElementAddress = FilesystemElementHelpers::GetListEntryAddressAt(parentToSearchIn, i);
//
//        cout << "Checking element at address: " << currentElementAddress << endl;
//
//        if (currentElement.Type == FilesystemElement::Directory)
//        {
//            if (currentElement.Name == nameToSearch)
//            {
//                cout << "Found matching name of element at address: " << currentElementAddress;
//
//                cout << "Its name is: " << currentElementAddress->Name << endl;
//
//                return currentElementAddress;
//            }
//        }
//    }
//
//    throw invalid_argument("Could not find child FilesystemElement with matching name");
//}

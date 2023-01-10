#include <iostream>
#include "ListProcessor.h"
#include "StringListHelpers.h"
#include "CharListHelpers.h"
#include "FileWorkers.h"
#include "DirectoryWorkers.h"
#include "FilesystemElementHelpers.h"

using namespace std;

void ListProcessor::ProcessList(list<string> inputList)
{
    list<FilesystemElement> topLevelList = BuildTree(inputList);

    cout << endl << " -----====== SWITCHING TO DIRECTORY SIZE READOUT =====------" << endl << endl;

    FilesystemElementHelpers::WalkAndPrintChildren(topLevelList);
}

list<FilesystemElement> ListProcessor::BuildTree(list<string> inputList)
{
    list<FilesystemElement> topLevelList;

    FilesystemElement topLevelDirectory("/", nullptr, FilesystemElement::Directory);

    topLevelList.push_back(topLevelDirectory);

    FilesystemElement* pCurrentDirectoryAddress = &topLevelList.back();

    bool inLsMode = false;

    for (auto currentLine : inputList)
    {
        cout << endl << "Current line: " << currentLine << endl << endl;

        // if command seen
        if (currentLine.rfind("$ ", 0) != string::npos)
        {
            cout << "Command seen!" << endl;

            // If we see a command then we're not looking at ls data anymore
            inLsMode = false;
        }

        if (inLsMode)
        {
            cout << "Reading ls line!" << endl;

            // If this flag is set, we know the lines that come after when it's set is data from a ls command
            if (currentLine.rfind("dir ", 0) != string::npos)
            {
                // Then we know we're getting a ls line about a directory

                cout << "Found directory info line!" << endl;

                cout << "Directory name is: " << currentLine.substr(4) << "!" << endl;

                cout << "Directory parent name is: " << pCurrentDirectoryAddress->Name << "!" << endl;

                string directoryName = currentLine.substr(4);

                FilesystemElement newChildDirectory(
                        directoryName,
                        pCurrentDirectoryAddress,
                        FilesystemElement::Directory);

                pCurrentDirectoryAddress->Children.push_back(newChildDirectory);
            }
            else
            {
                // Then we know we're getting a ls line about a file

                cout << "Found file info line!" << endl;

                cout << "File name is: " << FileWorkers::GetFileName(currentLine) << "!" << endl;
                cout << "File size is: " << FileWorkers::GetFileSize(currentLine) << "!" << endl;

                cout << "File parent name is: " << pCurrentDirectoryAddress->Name << "!" << endl;
                cout << "Directory parent address is: " << pCurrentDirectoryAddress << "!" << endl;

                FilesystemElement newChildFile(
                        FileWorkers::GetFileName(currentLine),
                        pCurrentDirectoryAddress,
                        FilesystemElement::File,
                        FileWorkers::GetFileSize(currentLine));

                pCurrentDirectoryAddress->Children.push_back(newChildFile);
            }
        }

        // if command seen
        if (currentLine.rfind("$ ", 0) != string::npos)
        {
            // if: cd .. then make pCurrentDirectoryAddress(*pCurrentDirectoryAddress).pParentAddress
            if (currentLine == "$ cd ..")
            {
                cout << "Going to parent. CurrentDirectory was: " << pCurrentDirectoryAddress->Name << "!" << endl;

                pCurrentDirectoryAddress = pCurrentDirectoryAddress->pParentAddress;

                cout << "Going to parent. CurrentDirectory is now: " << pCurrentDirectoryAddress->Name << "!" << endl;

                continue;
            }

            // if: cd / then skip it, only happens once at first line. Anything else,
            if (currentLine.rfind("$ cd ", 0) != string::npos &&
                currentLine.rfind("/", 5)  == string::npos)
            {
                string nameToFind = currentLine.substr(5);

                cout << "Searching for directory named: " << nameToFind << " in children" << endl;
                cout << "CurrentDirectory name was: " << pCurrentDirectoryAddress->Name << "!" << endl;
                cout << "CurrentDirectory address was: " << pCurrentDirectoryAddress << "!" << endl;

                list<FilesystemElement>& childrenToSearch = pCurrentDirectoryAddress->Children;

                auto it = childrenToSearch.begin();

                for(auto it = childrenToSearch.begin(); it != childrenToSearch.end(); it++)
                {
                    if (it->Name == nameToFind)
                    {
                        pCurrentDirectoryAddress = &(*it);
                    }
                }

                cout << "CurrentDirectory is now: " << pCurrentDirectoryAddress->Name << "!" << endl;
                cout << "CurrentDirectory address is now: " << pCurrentDirectoryAddress << "!" << endl;

                continue;
            }

            // if: ls then add things that come after if they don't start with $
            if (currentLine == "$ ls")
            {
                inLsMode = true;

                cout << "Switching to LS mode. Subsequent lines will be read as file or directory info" << endl;

                continue;
            }
        }
    };

    return topLevelList;
}
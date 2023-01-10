#include <iostream>
#include <string>
#include "FileWorkers.h"

using namespace std;

string FileWorkers::GetFileName(string lsLine)
{
    string fileName;

    for (char i : lsLine)
    {
        if (!isdigit(i))
        {
            fileName += i;
        }
    }

    return fileName.substr(1);
}

int FileWorkers::GetFileSize(string lsLine)
{
    string fileSizeString = "";

    for (char i : lsLine)
    {
        if (isdigit(i))
        {
            fileSizeString += i;
        }
    }

    int fileSizeInt = stoi(fileSizeString);

    return fileSizeInt;
}

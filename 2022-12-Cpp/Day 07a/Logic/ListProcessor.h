//
// Created by David on 12/23/2022.
//

#ifndef DAY_01_LISTPROCESSOR_H
#define DAY_01_LISTPROCESSOR_H

#include <string>
#include <list>
#include "../Models/FilesystemElement.h"

using namespace std;

class ListProcessor
{
public:
    static void ProcessList(list<string> inputList);

private:
    static list<FilesystemElement> BuildTree(list<string> inputList);
};


#endif //DAY_01_LISTPROCESSOR_H

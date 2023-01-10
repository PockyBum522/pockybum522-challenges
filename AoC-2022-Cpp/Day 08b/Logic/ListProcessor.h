//
// Created by David on 12/23/2022.
//

#ifndef DAY_01_LISTPROCESSOR_H
#define DAY_01_LISTPROCESSOR_H

#include <string>
#include <list>

using namespace std;

class ListProcessor
{
public:
    static void ConsoleWriteLine(string&& message, int newLinesFollowing = 1, bool forceWrite = false);

    static void ProcessList(list<string>& inputList);

    static int calculateTreeScoreAt(int x, int y, list<string> inputList);

    static int calculateScoreToLeftOf(int x, int y, string& currentRow);

    static int calculateScoreToRightOf(int x, int y, string& currentRow);

    static int calculateScoreToNorthOf(int x, int y, list<string>& inputList);

    static int calculateScoreToSouthOf(int x, int y, list<string>& inputList);

    static long GetTreeIntAt(int x, int y, list<string> list1);
};


#endif //DAY_01_LISTPROCESSOR_H

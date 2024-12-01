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
    static void ConsoleWriteLine(string&& message, int newLinesFollowing = 1);

    static void ProcessList(list<string>& inputList);

    static bool treeIsVisibleAt(int x, int y, list<string> inputList);

    static bool treeVisibleBecauseOfTreesInRow(int x, int y, string& currentRow);

    static bool treeVisibleBecauseOfTreesInColumn(int x, int y, list<string>& inputList);

    static bool treeVisibleBecauseOfTreesToItsLeft(int x, int y, string& currentRow);

    static bool treeVisibleBecauseOfTreesToItsRight(int x, int y, string& currentRow);

    static bool treeVisibleBecauseOfTreesToItsNorth(int x, int y, list<string>& inputList);

    static bool treeVisibleBecauseOfTreesToItsSouth(int x, int y, list<string>& inputList);

    static long GetTreeIntAt(int x, int y, list<string> list1);
};


#endif //DAY_01_LISTPROCESSOR_H

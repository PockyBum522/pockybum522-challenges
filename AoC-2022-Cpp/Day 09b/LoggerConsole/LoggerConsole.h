#ifndef DAY_01_LOGGERCONSOLE_H
#define DAY_01_LOGGERCONSOLE_H


#include <string>
#include <iostream>

using namespace std;

class LoggerConsole {
public:
    static bool ConsoleLogMessagesEnabled;

    static void WriteLine(string&& message, int newLinesFollowing = 1, bool forceWrite = false);
};


#endif //DAY_01_LOGGERCONSOLE_H

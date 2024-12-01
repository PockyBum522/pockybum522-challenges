#include "LoggerConsole.h"

using namespace std;

bool LoggerConsole::ConsoleLogMessagesEnabled;

void LoggerConsole::WriteLine(string&& message, int newLinesFollowing, bool forceWrite)
{
    if (!ConsoleLogMessagesEnabled && !forceWrite)
        return;

    cout << message;

    for (int i = 0; i < newLinesFollowing; i++)
        cout << endl;
}

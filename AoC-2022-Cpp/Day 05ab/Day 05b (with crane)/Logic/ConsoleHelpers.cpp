#include <minwindef.h>
#include <windows.h>
#include "ConsoleHelpers.h"

COORD pos;
HANDLE hConsole_c;
DWORD dwBytesWritten;

void ConsoleHelpers::Initialize()
{
    pos = {static_cast<SHORT>(1), static_cast<SHORT>(1)};

    hConsole_c = CreateConsoleScreenBuffer( GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole_c);

    dwBytesWritten = 0;
}

void ConsoleHelpers::DrawCharacterAt(char toDraw, int drawAtX, int drawAtY)
{
    pos = {static_cast<SHORT>(drawAtX), static_cast<SHORT>(drawAtY)};

    dwBytesWritten = 0;

    WriteConsoleOutputCharacter(hConsole_c, &toDraw, 1, pos, &dwBytesWritten);
}
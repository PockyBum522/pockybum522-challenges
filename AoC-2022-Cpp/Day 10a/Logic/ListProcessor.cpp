#include "ListProcessor.h"
#include "ListHelpers/CharListHelpers.h"
#include "../LoggerConsole/LoggerConsole.h"
#include "../Models/Board.h"
#include "../Models/Rope.h"
#include "../RawData/RawDataLoader/RawDataLoader.h"
#include "../RawData/RawData.h"

using namespace std;

void ListProcessor::ProcessList()
{
    list<string> inputList = RawDataLoader::LoadRawDataIntoList(RawData::INPUT_DATA_RAW);

    LoggerConsole::ConsoleLogMessagesEnabled = true;

    LoggerConsole::WriteLine("Initializing...");


}

char ListProcessor::GetDirectionCharacterFromLine(string dataLine)
{
    return dataLine[0];
}

int ListProcessor::GetNumberOfMovesFromLine(string dataLine)
{
    string currentlyParsedChars;

    for (int i = 0; i < dataLine.size(); i++)
    {
        if (isdigit(dataLine[i]))
            currentlyParsedChars += dataLine[i];
    }

    return stoi(currentlyParsedChars);
}

#include <list>
#include <string>
#include <sstream>
#include "RawDataLoader.h"

using namespace std;

list<string> RawDataLoader::LoadRawDataIntoList(string rawData)
{
    list<string> rawDataLines;

    string line;
    istringstream f(rawData);

    while (getline(f, line))
    {
        rawDataLines.push_back(line);
    }

    return rawDataLines;
}

#include <list>
#include <string>
#include <sstream>
#include "RawDataLoader.h"

std::list<std::string> RawDataLoader::LoadRawDataIntoList(std::string rawData)
{
    std::list<std::string> rawDataLines;

    std::string line;
    std::istringstream f(rawData);

    while (getline(f, line))
    {
        rawDataLines.push_back(line);
    }

    return rawDataLines;
}

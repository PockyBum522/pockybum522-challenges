#include <list>

#include "Logic/ListProcessor.h"
#include "Logic/RawDataLoader.h"
#include "RawData/RawData.h"

int main()
{
    std::list<std::string> rawDataLines = RawDataLoader::LoadRawDataIntoList(RawData::INPUT_DATA_RAW);

    ListProcessor::ProcessList(rawDataLines);

    return 0;
}
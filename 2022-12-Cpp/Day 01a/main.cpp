#include <iostream>
#include <sstream>
#include "RawData/RawData.h"

int main()
{
    int cumulation = 0;
    int counter = 0;
    int highestAmount = 0;
    int elfNumberWithHighestAmount = 0;

    std::string line;
    std::istringstream f(RawData::INPUT_DATA_RAW + "\n\n"); // Extra endl because that's what we're using

    while (std::getline(f, line))
    {
        if (line != "")
        {
            cumulation+=stoi(line);
        }
        else
        {
            std::cout << "Total for elf #" << ++counter << ": " << cumulation << std::endl;

            if (cumulation > highestAmount)
            {
                elfNumberWithHighestAmount = counter;
                highestAmount = cumulation;
            }

            cumulation = 0;
        }
    }

    std::cout <<  std::endl << std::endl << "Elf with highest amount: #" << elfNumberWithHighestAmount << std::endl;

    std::cout << "Highest amount: #" << highestAmount << std::endl;

    return 0;
}
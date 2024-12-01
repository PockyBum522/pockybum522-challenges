#include <iostream>
#include <sstream>
#include <list>
#include "RawData/RawData.h"

using namespace std;

int main()
{
    int cumulation = 0;
    int counter = 0;
    int highestAmount = 0;

    string line;
    istringstream f(RawData::INPUT_DATA_RAW + "\n\n"); // Extra endl because that's what we're using
    list<int> totals;

    while (getline(f, line))
    {
        if (line != "")
        {
            cumulation+=stoi(line);
        }
        else
        {
            cout << "Total for elf #" << ++counter << ": " << cumulation << endl;

            if (cumulation > highestAmount)
            {
                highestAmount = cumulation;

                totals.push_back(highestAmount);
            }

            cumulation = 0;
        }
    }

    for (int x : totals) {
        cout << x << '\n';
    }

    return 0;
}
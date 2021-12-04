#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <bitset>
#include <algorithm>


constexpr int dataWidth = 12;

int getCountOf(std::vector<std::bitset<dataWidth> > &data, int bitValue, int bitPos)
{
    int count = 0;
    for(const auto &it : data)
    {
        if(it[bitPos] == bitValue)
        {
            count++;
        }   
    }
    
    return count;
}

inline void erase(std::vector<std::bitset<dataWidth> > &data, int bitValue, int bitPos)
{
    data.erase(std::remove_if(data.begin(), data.end(), [bitPos, bitValue](std::bitset<dataWidth> x) { return x[bitPos] == bitValue; }), data.end());
}

int main()
{
   
    std::ifstream infile("input/day3");
    std::vector<std::bitset<dataWidth> > oxygenData = {};
    std::vector<std::bitset<dataWidth> > co2Data = {};
    std::bitset<dataWidth> input;

    int count = 0;

    while (infile >> input)
    {
        oxygenData.push_back(input);
    }

    co2Data = oxygenData;

    for(int bit = dataWidth - 1; bit >= 0; bit--)
    {
        if (oxygenData.size() > 1)
        {
            count = getCountOf(oxygenData, 1, bit);
            erase(oxygenData, (oxygenData.size() - count > oxygenData.size() / 2) ? 1 : 0, bit);
        }

        if (co2Data.size() > 1)
        {
            count = getCountOf(co2Data, 1, bit);
            erase(co2Data, (co2Data.size() - count > co2Data.size() / 2) ? 0 : 1, bit);
        }
    }

    std::cout << "oxygen " << oxygenData[0] << "::" << oxygenData[0].to_ulong() << std::endl;
    std::cout << "co2  " << co2Data[0] << "::" << co2Data[0].to_ulong() << std::endl;
    std::cout << "result " << oxygenData[0].to_ulong() * co2Data[0].to_ulong() << std::endl;

    return 0;
}
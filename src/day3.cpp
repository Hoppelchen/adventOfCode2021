#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <bitset>

int main()
{
   
    std::ifstream infile("input/day3");
    constexpr int dataWidth = 12;
    std::vector<std::bitset<dataWidth> > data = {};
    std::bitset<dataWidth> input;
    std::bitset<dataWidth> gammaRate = 0;
    std::bitset<dataWidth> epsilonRate = 0;
    int count[dataWidth] = { };

    while (infile >> input)
    {
        data.push_back(input);
    }

    for(const auto &it : data)
    {
        for(int bit = dataWidth - 1; bit >= 0; bit--)
        {
            if(it[bit] == 1)
            {
                count[bit]++;
            }
        }
    }

    for(auto i = 0; i < dataWidth; i++)
    {
        if (data.size() - count[i] > data.size() / 2)
        {
            gammaRate.set(i);
        }
    }

    epsilonRate = gammaRate;
    epsilonRate.flip();

    std::cout << "gammma " << gammaRate << "::" <<gammaRate.to_ulong() << std::endl;
    std::cout << "epsilon  " << epsilonRate << "::" <<epsilonRate.to_ulong() << std::endl;
    std::cout << "result=" << gammaRate.to_ulong() * epsilonRate.to_ulong() << std::endl;

    return 0;
}
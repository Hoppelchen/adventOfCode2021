#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

int main()
{
   
    std::ifstream infile("input/day7");

    std::string line;
    std::getline(infile, line);
    std::stringstream  stringstream(line);

    std::vector<int> input;
    int biggest = 0;
 

    for (int i; stringstream >> i;)
    {
        input.push_back(i);    
        if (stringstream.peek() == ',')
        {
            stringstream.ignore();
        }
    }
    
    // get biggest number
    for(const auto& i: input)
    {
        if (i > biggest)
        {
            biggest = i;
        }
    }

    std::vector<int> crapsOnIndex(biggest + 1, 0);

    // fill craps
    for(auto& crab : input)
    {
        crapsOnIndex[crab]++;
    }

    // calc result
    int lastResult = INT32_MAX;

    for (int i = 0; i <= biggest; i++)
    {
        int res = 0;
        for(int j = 0; j < static_cast<int>(crapsOnIndex.size()); j++)
        {
            if (crapsOnIndex[j] != 0)
            {
                res += abs(i - j) * crapsOnIndex[j] ;
            }
        }
        
        // distance is rising again, found minimum
        if (res > lastResult)
        {
            std::cout << "found destination index " << i - 1 << std::endl;
            break;
        }

        lastResult = res;
    }

    std::cout << "fuel needed " << lastResult << std::endl;

    return 0;
}
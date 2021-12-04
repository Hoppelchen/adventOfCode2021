#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int main()
{
    std::ifstream infile("input/day1");
    std::vector<int> data = {};
    int count = 0;
    int a = 0;
    while (infile >> a)
    {
        data.push_back(a);
    }

    std::cout << data[0] << " (N/A - no previous measurement)" << std::endl;
    for (int i = 1; i < (int)data.size(); i++)
    {
        std::cout << data[i];
        if (data[i - 1] < data[i])
        {
            std::cout << " (increased)" << std::endl;
            count++;
        }
        else
        {
            std::cout << " (decreased)" << std::endl;
        }
    }

    std::cout << "Result: " << count << std::endl;

    return 0;
}